#include <QtDBus>
#include "ServerConfig.h"
#include "qmlcontroller.h"


QmlController::QmlController(QObject *parent)
    : QObject{parent}, rpm(0), humidity(0), temperature(0),
      battery(0), speed(0)
{
    qDBusRegisterMetaType<struct Data>();
    dataManager = new local::DataManager("pi.chan", "/can/read",
                                         QDBusConnection::sessionBus(), this);

    connect(dataManager, SIGNAL(broadRpmSpeedChanged()), this, SLOT(updateRpmSpeed()));
    connect(dataManager, SIGNAL(broadHumTempChanged()), this, SLOT(updateTempHum()));
    //example how to use connect with function address
    connect(dataManager, &local::DataManager::broadBatteryChanged,
            this, &QmlController::updateBattery);
}

void QmlController::updateRpmSpeed()
{
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << "Bus connected error";
        return ;
    }
    QDBusPendingReply<int> rpm = dataManager->fetchRpmFromServer();
    QDBusPendingReply<int> speed = dataManager->fetchSpeedFromServer();
    if (!rpm.isError() && !speed.isError())
    {
        qDebug() << "Rpm data fetch success : " << rpm.value();
        qDebug() << "Speed data fetch success : " << speed.value();
        setRpm(rpm.value());
        setSpeed(speed.value());
    }
    else
    {
        qDebug() << "reply is not valid";
        qDebug() << rpm.error();
        qDebug() << speed.error();
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


