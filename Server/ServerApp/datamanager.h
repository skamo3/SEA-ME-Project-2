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
    explicit DataManager(const QString &ifname, QObject *parent = nullptr);
    void updateData();

private:
    struct Data sensorData;
    class CANSocket *canSocket;


    explicit DataManager(QObject *parent = nullptr);

signals:

public slots:
    Q_SCRIPTABLE struct Data dataShare();

};

#endif // DATAMANAGER_H
