#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>
#include "datamanager_interface.h"

class QmlController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rpm READ getRpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(int humidity READ getHumidity WRITE setHumidity NOTIFY humidityChanged)
    Q_PROPERTY(int temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(int battery READ getBattery WRITE setBattery NOTIFY batteryChanged)
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
public:
    explicit QmlController(QObject *parent = nullptr);

    int getRpm() const;
    void setRpm(int newRpm);

    int getHumidity() const;
    void setHumidity(int newHumidity);

    int getTemperature() const;
    void setTemperature(int newTemperature);

    int getBattery() const;
    void setBattery(int newBattery);

    int getSpeed() const;
    void setSpeed(int newSpeed);

private:
    int rpm;
    int humidity;
    int temperature;
    int battery;
    int speed;

    local::DataManager *dataManager;

signals:
    void rpmChanged();
    void humidityChanged();
    void temperatureChanged();
    void batteryChanged();
    void speedChanged();

public slots:
    void updateRpmSpeed();
    void updateBattery();
    void updateTempHum();


};

#endif // QMLCONTROLLER_H
