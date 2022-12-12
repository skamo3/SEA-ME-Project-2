#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QObject>
#include <QMetaType>
#include <QtDBus>

#define SERVICE_NAME "pi.chan"

struct Data {
    int rpm;
    int temp;
    int hum;
    int battery;
    int speed;

    friend QDBusArgument &operator<<(QDBusArgument &arg, const struct Data &data)
    {
        arg.beginStructure();
        arg << data.rpm;
        arg << data.temp;
        arg << data.hum;
        arg << data.battery;
        arg.endStructure();
        return arg;
    }

    friend const QDBusArgument &operator>>(const QDBusArgument &arg, struct Data &data)
    {
        arg.beginStructure();
        qDebug() << "najsndjansd";
        arg >> data.rpm;
        arg >> data.temp;
        arg >> data.hum;
        arg >> data.battery;
        arg.endStructure();
        return arg;
    }

};

Q_DECLARE_METATYPE(Data);



#endif // SERVERCONFIG_H
