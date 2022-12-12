#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <QTimer>
#include "ServerConfig.h"
#include "ina219.h"
#include "canreceiver.h"

CanReceiver::CanReceiver(QObject *parent)
    : QObject{parent}, socketFD(0), canData(new struct Data), inaStatus(0),
      ina219(NULL), canTimer(std::make_shared<QTimer>()),
      batteryTimer(std::make_shared<QTimer>())
{
//    qDBusRegisterMetaType<struct Data>();
    connect(canTimer.get(), SIGNAL(timeout()), this, SLOT(readData()));
    connect(batteryTimer.get(), SIGNAL(timeout()), this, SLOT(readBatteryData()));
}

CanReceiver::CanReceiver(const CanReceiver &origin)
    : QObject{this->parent()}, socketFD(origin.socketFD), canFrame(origin.canFrame)
{
}

CanReceiver &CanReceiver::operator=(const CanReceiver &origin)
{
    if (this != &origin)
    {
        socketFD = origin.socketFD;
        canFrame = origin.canFrame;
    }
    return *this;
}

CanReceiver::~CanReceiver()
{
    if (socketFD > 0)
        close(socketFD);
}

void CanReceiver::initSocket(const QString &ifname)
{
    socketFD = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socketFD < 0)
    {
        qDebug() << COLOR_BRED << "Failed to socket create" << COLOR_RESET;
        exit(socketFD);
    }
    qDebug() << COLOR_BGREEN << "Success to socket create" << COLOR_RESET;

    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifname.toStdString().c_str());
    int ret = ioctl(socketFD, SIOCGIFINDEX, &ifr);
    if (ret < 0)
    {
        qDebug() << COLOR_BRED << "Failed to get CAN interface index" << COLOR_RESET;
        exit(ret);
    }
    qDebug() << COLOR_BGREEN << "Success to get CAN interface index : " << ret << COLOR_RESET;

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(socketFD, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        qDebug() << COLOR_BRED << "Failed to socket bind" << COLOR_RESET;
        qDebug() << COLOR_RED << "Error code : " << ret << COLOR_RESET;
        exit(ret);
    }
    qDebug() << COLOR_BGREEN << "Success to socket bind" << COLOR_RESET;
}

int CanReceiver::readData()
{
    int rd_byte = read(socketFD, &canFrame, sizeof(canFrame));
    if (rd_byte < 0)
    {
        qDebug() << COLOR_BRED << "Failed to recieve CAN frame" << COLOR_RESET;
        return rd_byte;
    }

    if (canFrame.data[0] != canData->hum || canFrame.data[1] != canData->temp)
    {
        canData->hum = canFrame.data[0];
        canData->temp = canFrame.data[1];
        sendHumTempDataToServer();
    }

    if (canData->rpm != (canFrame.data[2] | uint16_t(canFrame.data[3]) << 8)
            || canData->speed != canFrame.data[4])
    {
        canData->rpm = canFrame.data[2] | uint16_t(canFrame.data[3]) << 8;
        canData->speed = canFrame.data[4];
        sendRpmSpeedDataToServer();
    }

    return rd_byte;
}

void CanReceiver::initDBusServer(const QString &serverName, const QString &objName)
{
    dataManager = new local::DataManager(serverName, objName,
                                         QDBusConnection::sessionBus(), this);
    qDebug() << COLOR_BGREEN << "Success to open Dbus server" << COLOR_RESET;
}

void CanReceiver::startCommunicate()
{
    int intervals = 10;
    inaStatus = initBatteryLine();

    canTimer->start(intervals);
    batteryTimer->start(5000);
}

int CanReceiver::initBatteryLine()
{
    ina219 = ina219_create(I2C_DEV, I2C_ADDR, SHUNT_MILLIOHMS,
                           BATTERY_VOLTAGE_0_PERCENT, BATTERY_VOLTAGE_100_PERCENT,
                           BATTERY_CAPACITY, MIN_CHARGING_CURRENT);
    char *error = NULL;
    if (!ina219_init(ina219, &error))
    {
        qDebug() << QString("Battery line init fail %1").arg(error);
        return 0;
    }
    qDebug() << COLOR_BGREEN << "Success to battery line init" << COLOR_RESET;
    return 1;
}

void CanReceiver::sendHumTempDataToServer()
{
    qDebug() << "send hum temp data from can receiver";
    dataManager->saveHumTempInServer(canData->hum, canData->temp);
}

void CanReceiver::sendRpmSpeedDataToServer()
{
    qDebug() << "send rpm speed data from can receiver";
    dataManager->saveRpmSpeedInServer(canData->rpm, canData->speed);
}

void CanReceiver::sendBatteryDataToServer()
{
    qDebug() << "send battery data from can receiver";
    dataManager->saveBatteryLVInServer(canData->battery);
}

void CanReceiver::readBatteryData()
{
    int mV;
    int percent_charged;
    int battery_current_mA;
    int minutes;
    INA219ChargeStatus charge_status;
    char *error;
    if (inaStatus == 1 &&
            ina219_get_status(ina219, &charge_status,
                              &mV, &percent_charged, &battery_current_mA,
                              &minutes, &error))
    {
        if (canData->battery != percent_charged)
        {
            canData->battery = percent_charged;
            sendBatteryDataToServer();
        }
    }
    else
    {
        qDebug() << COLOR_BRED << "Failed to get battery : " << error << COLOR_RESET;
    }
}
