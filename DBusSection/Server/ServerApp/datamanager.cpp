#include "cansocket.h"
#include "datamanager.h"
#include <QDebug>
#include "datamanager_adaptor.h"

DataManager::DataManager(const QString &ifname, QObject *parent)
    : QObject{parent}, canSocket(new CANSocket)
{
//    canSocket->initSocket(ifname);
    new DataManagerAdaptor(this);
}
void DataManager::updateData()
{
//    canSocket->readData(sensorData);
    qDebug() << "Test receive sensor data";
    qDebug() << "RPM : " << sensorData.rpm;
}

QString DataManager::dataShare()
{
    qDebug() << "Data Sending";
    return QString("return test");
}
