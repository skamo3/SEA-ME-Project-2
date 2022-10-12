#include <QtDBus/QtDBus>
#include <QDebug>
#include "testobj.h"

QString TestObj::ping(const QString &arg)
{
    qDebug() << "test plz ";
    QMetaObject::invokeMethod(QCoreApplication::instance(), "quit");
    return QString("ping(\"%1\") got called").arg(arg);
}
