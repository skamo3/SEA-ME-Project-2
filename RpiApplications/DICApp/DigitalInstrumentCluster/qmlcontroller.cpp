#include <QtDBus>
#include "qmlcontroller.h"
#include <QtQuick/QtQuick>
#include "ServerConfig.h"

QmlController::QmlController(QObject *parent)
    : QObject{parent}, rpm(0), timer(std::make_shared<QTimer>())
{
    dataManager = new local::DataManager("pi.chan", "/can/read",
                                         QDBusConnection::sessionBus(), this);

    connect(timer.get(), SIGNAL(timeout()), this, SLOT(testFunc()));
    timer->setInterval(1000);
    timer->start();
}

void QmlController::getData()
{
//    if (QDBusConnection::sessionBus().isConnected())
//        qDebug() << "Bus connected";
//    QDBusPendingReply<int> reply =  dataManager->fetchRpmFromServer();
//    if (!reply.isError())
//    {
//        qDebug() << "data recieved : " << reply.value();
//        printable = QVariant(reply.value()).toString();
//    } else {
//        qDebug() << "reply is not valid";
//        qDebug() << reply.error();
//    }
    //    emit valueChanged();
}

void QmlController::updateData()
{
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << "Bus connected error";
        return ;
    }
    QDBusPendingReply<QDBusVariant> reply = dataManager->fetchAllDataFromServer();
    if (!reply.isError())
    {
        qDebug() << "data receive success";
        QVariant replyData;
        replyData.setValue(reply);
        struct Data sensorData = replyData.value<struct Data>();
        setRpm(sensorData.rpm);
        setHumidity(sensorData.hum);
        setTemperature(sensorData.temp);
        setBattery(sensorData.battery);
    }
    else
    {
        qDebug() << "reply is not valid";
        qDebug() << reply.error();
    }
}

int QmlController::getRpm() const
{
    return rpm;
}

void QmlController::setRpm(int newRpm)
{
    if (rpm == newRpm)
        return;
    rpm = newRpm;
    emit rpmChanged();
}

int QmlController::getHumidity() const
{
    return humidity;
}

void QmlController::setHumidity(int newHumidity)
{
    if (humidity == newHumidity)
        return;
    humidity = newHumidity;
    emit humidityChanged();
}

int QmlController::getTemperature() const
{
    return temperature;
}

void QmlController::setTemperature(int newTemperature)
{
    if (temperature == newTemperature)
        return;
    temperature = newTemperature;
    emit temperatureChanged();
}

int QmlController::getBattery() const
{
    return battery;
}

void QmlController::setBattery(int newBattery)
{
    if (battery == newBattery)
        return;
    battery = newBattery;
    emit batteryChanged();
}

int QmlController::getSpeed() const
{
    return speed;
}

void QmlController::setSpeed(int newSpeed)
{
    if (speed == newSpeed)
        return;
    speed = newSpeed;
    emit speedChanged();
}

void QmlController::testFunc()
{
    qDebug() << "test func called : " << rpm;
    int ran = QRandomGenerator::global()->bounded(0, 5000);
    setRpm(ran);
    setTemperature(QRandomGenerator::global()->bounded(0, 50));
    setHumidity(QRandomGenerator::global()->bounded(0, 50));
}

