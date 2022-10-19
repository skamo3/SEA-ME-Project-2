#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>
#include "datamanager_interface.h"

class QmlController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString printable READ getValue NOTIFY valueChanged)
public:
    explicit QmlController(QObject *parent = nullptr);



    Q_INVOKABLE QString getValue() const;

private:
    QString printable;
    local::DataManager *dataManager;
    std::shared_ptr<class QTimer> timer;

signals:
    void valueChanged();

public slots:
    Q_INVOKABLE void getData();

};

#endif // QMLCONTROLLER_H
