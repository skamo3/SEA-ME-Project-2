#include <QCoreApplication>
#include <QtDBus/QtDBus>
#include <QDebug>
#include "datamanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    if (!connection.registerService("pi.chan")) {
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    DataManager dataManager("can0");

    connection.registerObject("/can", &dataManager);

    while (1)
    {
        dataManager.updateData();
        QThread::sleep(1);
    }


    return a.exec();
}
