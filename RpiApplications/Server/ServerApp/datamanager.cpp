#include "datamanager.h"
#include <QDebug>
#include "datamanager_adaptor.h"
#include "ServerConfig.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}, sensorData(), signalTimer(std::make_shared<QTimer>())
{
    new DataManagerAdaptor(this);

}

void DataManager::saveRpmSpeedInServer(int rpm, int speed)
{
    if (sensorData.rpm != rpm || sensorData.speed != speed)
    {
        sensorData.rpm = rpm;
        sensorData.speed = speed;
        // call broadcast
        emit broadRpmSpeedChanged();
    }
}

void DataManager::saveHumTempInServer(int hum, int temp)
{
    if (sensorData.hum != hum || sensorData.temp != temp)
    {
        sensorData.hum = hum;
        sensorData.temp = temp;
        // call broadcast
        emit broadHumTempChanged();
    }
}

void DataManager::saveBatteryLVInServer(int battery)
{
    if (sensorData.battery != battery)
    {
        sensorData.battery = battery;
        // call broadcast
        emit broadBatteryChanged();
    }
}


int DataManager::fetchRpmFromServer()
{
    qDebug() << "seding rpm data";
    return sensorData.rpm;
}

int DataManager::fetchTempFromServer()
{
    qDebug() << "seding temp data";
    return sensorData.temp;
}

int DataManager::fetchHumFromServer()
{
    qDebug() << "seding hum data";
    return sensorData.hum;
}

int DataManager::fetchBtrLvFromServer()
{
    qDebug() << "seding batter data";
    return sensorData.battery;
}

int DataManager::fetchSpeedFromServer()
{
    qDebug() << "seding batter data";
    return sensorData.speed;
}

