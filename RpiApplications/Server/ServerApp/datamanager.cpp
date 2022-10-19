#include "datamanager.h"
#include <QDebug>
#include "datamanager_adaptor.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
    new DataManagerAdaptor(this);
}

void DataManager::saveCanDataInServer()
{
    qDebug() << "can data save function called";
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
