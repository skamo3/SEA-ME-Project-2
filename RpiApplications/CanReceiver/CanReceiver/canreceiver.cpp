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
#include "canreceiver.h"
#include <QDebug>
#include <QTimer>
#include "ServerConfig.h"

CanReceiver::CanReceiver(QObject *parent)
    : QObject{parent}, canTimer(std::make_shared<QTimer>()),
      dbusTimer(std::make_shared<QTimer>())
{
    qDBusRegisterMetaType<struct Data>();
    connect(canTimer.get(), SIGNAL(timeout()), this, SLOT(readData()));
    connect(dbusTimer.get(), SIGNAL(timeout()), this, SLOT(sendCanDataToServer()));
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

    std::cout << "ID =>[0x" << std::hex << canFrame.can_id << "] | size{" << int(canFrame.can_dlc) << "}" << std::endl;

    for (int i = 0; i < canFrame.can_dlc; i++)
        std::cout << std::hex << int(canFrame.data[i]) << " : ";
    std::cout << std::endl;

    int rpm = (canFrame.data[0] * 256) + canFrame.data[1];

    std::cout << "RPM : " << std::dec << rpm << std::endl;

    return rd_byte;
}

void CanReceiver::initDBusServer(const QString &serverName, const QString &objName)
{
    dataManager = new local::DataManager(serverName, objName,
                                         QDBusConnection::sessionBus(), this);
}

void CanReceiver::startCommunicate()
{
    int intervals = 10;
    canTimer->start(intervals);
    dbusTimer->start(intervals);
}

void CanReceiver::sendCanDataToServer()
{
    if (socketFD < 0)
    {
        qDebug() << "Can socket is not open";
        return;
    }
    if (!dataManager)
    {
        qDebug() << "D-Bus session is not open";
        return;
    }
    struct Data canData;
    canData.rpm = (canFrame.data[0] * 256) + canFrame.data[1];
    QVariant v;
    v.setValue(canData);
    QDBusVariant da;
    da.setVariant(v);
    qDebug() << "rpm : " << canData.rpm;
    dataManager->saveCanDataInServer(da);
}
