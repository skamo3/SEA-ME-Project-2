#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

struct Data {
    int rpm;
    int temp;
    int hum;
    int battery;
};

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

private:
    struct Data sensorData;

signals:

public slots:
    void saveCanDataInServer();

    int fetchRpmFromServer();
    int fetchTempFromServer();
    int fetchHumFromServer();
    int fetchBtrLvFromServer();

};

#endif // DATAMANAGER_H
