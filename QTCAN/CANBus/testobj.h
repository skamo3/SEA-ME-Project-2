#ifndef TESTOBJ_H
#define TESTOBJ_H

#include <QObject>

class TestObj : public QObject
{
    Q_OBJECT

public slots:
    Q_SCRIPTABLE QString ping(const QString &arg);

};

#endif // TESTOBJ_H
