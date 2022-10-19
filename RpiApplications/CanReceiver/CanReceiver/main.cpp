#include <QCoreApplication>
#include <QDebug>
#include "canreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CanReceiver canReceiver;
    canReceiver.initSocket("can0");
    canReceiver.initDBusServer("pi.chan", "/can/write");

    canReceiver.startCommunicate();

    return a.exec();
}
