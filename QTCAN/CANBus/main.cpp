#include <QCoreApplication>
#include <QDebug>
#include <QtDBus/QtDBus>
#include "../../Server/includes/CANSocket.hpp"
#include "testobj.h"

int main(int argc, char *argv[])
{
    CANSocket canSocket;

    canSocket.initSocket("can0");

    QCoreApplication a(argc, argv);

    canSocket.readData();

    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerService("org.test")) {
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    TestObj test;
    QDBusConnection::sessionBus().registerObject("/", &test, QDBusConnection::ExportAllSlots);

    return a.exec();
}
