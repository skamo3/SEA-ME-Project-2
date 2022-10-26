#include <QtDBus>
#include "ServerConfig.h"
#include "qmlcontroller.h"


QmlController::QmlController(QObject *parent)
    : QObject{parent}, rpm(0), rpmTimer(std::make_shared<QTimer>()),
      batteryTimer(std::make_shared<QTimer>()), tempHumTimer(std::make_shared<QTimer>())
{
    qDBusRegisterMetaType<struct Data>();
    dataManager = new local::DataManager("pi.chan", "/can/read",
                                         QDBusConnection::sessionBus(), this);

    connect(rpmTimer.get(), SIGNAL(timeout()), this, SLOT(updateRpm()));
    connect(batteryTimer.get(), SIGNAL(timeout()), this, SLOT(updateBattery()));
    connect(tempHumTimer.get(), SIGNAL(timeout()), this, SLOT(updateTempHum()));

    rpmTimer->setInterval(2000);
    batteryTimer->setInterval(5000);
    tempHumTimer->setInterval(10000);

    rpmTimer->start();
    batteryTimer->start();
    tempHumTimer->start();
}

void QmlController::updateRpm()
{
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << "Bus connected error";
        return ;
    }
    QDBusPendingReply<int> reply = dataManager->fetchRpmFromServer();
    if (!reply.isError())
    {
        qDebug() << "Rpm data fetch success : " << reply.value();
        setRpm(reply.value());
    }
    else
    {
        qDebug() << "reply is not valid";
        qDebug() << reply.error();
    }
}

void QmlController::updateBattery()
{
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << "Bus connected error";
        return ;
    }
    QDBusPendingReply<int> reply = dataManager->fetchBtrLvFromServer();
    if (!reply.isError())
    {
        qDebug() << "Battery data fetch success : " << reply.value();
        setBattery(reply.value());
    }
    else
    {
        qDebug() << "reply is not valid";
        qDebug() << reply.error();
    }
}

void QmlController::updateTempHum()
{
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << "Bus connected error";
        return ;
    }
    QDBusPendingReply<int> temp = dataManager->fetchBtrLvFromServer();
    QDBusPendingReply<int> hum = dataManager->fetchBtrLvFromServer();
    if (!temp.isError() && !hum.isError())
    {
        qDebug() << "Temp data fetch success : " << temp.value();
        qDebug() << "Hum data fetch success : " << temp.value();
        setTemperature(temp.value());
        setTemperature(hum.value());
    }
    else
    {
        qDebug() << "reply is not valid";
        qDebug() << temp.error();
        qDebug() << hum.isError();
    }
}

int QmlController::getRpm() const
{
    return rpm;
}

void QmlController::setRpm(int newRpm)
{
    if (rpm == newRpm && newRpm < 0)
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
    if (humidity == newHumidity && newHumidity < 0)
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
    if (temperature == newTemperature && newTemperature < -20)
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
    if (battery == newBattery && newBattery < 0)
        return;
    battery = newBattery;
    qDebug() << "Battery percent : " << battery;
    emit batteryChanged();
}

int QmlController::getSpeed() const
{
    return speed;
}

void QmlController::setSpeed(int newSpeed)
{
    if (speed == newSpeed && newSpeed < 0)
        return;
    speed = newSpeed;
    emit speedChanged();
}


