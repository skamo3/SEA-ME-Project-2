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
    if (reply.isValid())
    {
        QString ret = dataManager->dataShare();
        qDebug() << "data recieved : " << ret;
        printable = ret;
    } else {
        qDebug() << "reply is not valid";
        qDebug() << reply.error();
    }

    qDebug() << "count : " << reply.count();

    QString ret = dataManager->dataShare();
    qDebug() << "data recieved : " << ret;


    emit valueChanged();
}

QString QmlController::getValue() const
{
    return printable;
}
