#include <QtDBus>
#include "qmlcontroller.h"

QmlController::QmlController(QObject *parent)
    : QObject{parent}, printable("")
{
    dataManager = new local::DataManager("pi.chan", "/can",
                                         QDBusConnection::sessionBus(), this);


}

void QmlController::getData()
{
    if (QDBusConnection::sessionBus().isConnected())
        qDebug() << "Bus connected";
    qDebug() << "It's here!!";
    qDebug() << "test: " << dataManager->isValid();
    QDBusPendingReply<QString> reply =  dataManager->dataShare();
    if (!reply.isError())
    {
        qDebug() << "data recieved : " << reply.value();
        printable = reply.value();
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
