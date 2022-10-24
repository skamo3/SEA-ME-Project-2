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

signals:

public slots:
    void saveCanDataInServer(QDBusVariant data);

    QDBusVariant fetchAllDataFromServer();

    int fetchRpmFromServer();
    int fetchTempFromServer();
    int fetchHumFromServer();
    int fetchBtrLvFromServer();

};

#endif // DATAMANAGER_H
