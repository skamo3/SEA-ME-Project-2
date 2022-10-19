#include <QtDBus>
#include "qmlcontroller.h"

QmlController::QmlController(QObject *parent)
    : QObject{parent}, printable(""), timer(std::make_shared<QTimer>())
{
    dataManager = new local::DataManager("pi.chan", "/can/read",
                                         QDBusConnection::sessionBus(), this);

    connect(timer.get(), SIGNAL(timeout()), this, SLOT(getData()));
    timer->start();
}

void QmlController::getData()
{
    if (QDBusConnection::sessionBus().isConnected())
        qDebug() << "Bus connected";
    QDBusPendingReply<int> reply =  dataManager->fetchRpmFromServer();
    if (!reply.isError())
    {
        qDebug() << "data recieved : " << reply.value();
        printable = QVariant(reply.value()).toString();
    } else {
        qDebug() << "reply is not valid";
        qDebug() << reply.error();
    }

    emit valueChanged();
}

QString QmlController::getValue() const
{
    return printable;
}
