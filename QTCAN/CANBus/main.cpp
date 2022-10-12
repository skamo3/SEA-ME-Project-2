#include <QCoreApplication>
#include <QDebug>
#include "../../Server/includes/CANSocket.hpp"

int main(int argc, char *argv[])
{
    CANSocket canSocket;

    canSocket.initSocket("can0");

    QCoreApplication a(argc, argv);

    canSocket.readData();
    qDebug() << canSocket.getCanFrame().data[0];

    return a.exec();
}
