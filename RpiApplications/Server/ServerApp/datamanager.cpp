#include "datamanager.h"
#include <QDebug>
#include "datamanager_adaptor.h"
#include "ServerConfig.h"
#include "qdbusargument.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
    new DataManagerAdaptor(this);
    qDBusRegisterMetaType<struct Data>();
}

void DataManager::saveCanDataInServer(QDBusVariant data)
{
    qDebug() << "can data save function called";
    sensorData = qdbus_cast<struct Data>(QVariant(data.variant()));

    qDebug() << "rpm : " << sensorData.rpm;
    qDebug() << "temp : " << sensorData.temp;
    qDebug() << "hum : " << sensorData.hum;
    qDebug() << "battery : " << sensorData.battery;
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
