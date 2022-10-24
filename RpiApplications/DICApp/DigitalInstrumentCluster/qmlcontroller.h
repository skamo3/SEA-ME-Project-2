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

private:
    int rpm;
    int humidity;
    int temperature;
    int battery;

    local::DataManager *dataManager;
    std::shared_ptr<class QTimer> timer;

signals:
    void rpmChanged();
    void humidityChanged();
    void temperatureChanged();
    void batteryChanged();

public slots:
    Q_INVOKABLE void getData();
    void updateData();
    void testFunc();

};

#endif // QMLCONTROLLER_H
