#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QtDBus>
#include "ServerConfig.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

private:
    struct Data sensorData;


    std::shared_ptr<class QTimer> signalTimer;

signals:
    void broadRpmSpeedChanged();
    void broadHumTempChanged();
    void broadBatteryChanged();


public slots:
    void saveRpmSpeedInServer(int rpm, int speed);
    void saveHumTempInServer(int hum, int temp);
    void saveBatteryLVInServer(int battery);

    int fetchRpmFromServer();
    int fetchTempFromServer();
    int fetchHumFromServer();
    int fetchBtrLvFromServer();
    int fetchSpeedFromServer();

};

#endif // DATAMANAGER_H
