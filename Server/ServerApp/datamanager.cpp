#include "cansocket.h"
#include "datamanager.h"
#include <QDebug>

DataManager::DataManager(const QString &ifname, QObject *parent)
    : QObject{parent}, canSocket(new CANSocket)
{
    canSocket->initSocket(ifname);
}
void DataManager::updateData()
{
    canSocket->readData(sensorData);
    qDebug() << "Test receive sensor data";
    qDebug() << "RPM : " << sensorData.rpm;
}

Data DataManager::dataShare()
{
    qDebug() << "Data Sending";
    return sensorData;
}
