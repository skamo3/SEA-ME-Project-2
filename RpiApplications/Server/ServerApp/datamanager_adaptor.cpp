/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -i datamanager_adaptor.h -a :datamanager_adaptor.cpp ../../interfaces/datamanager.xml
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "datamanager_adaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class DataManagerAdaptor
 */

DataManagerAdaptor::DataManagerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DataManagerAdaptor::~DataManagerAdaptor()
{
    // destructor
}

int DataManagerAdaptor::fetchBtrLvFromServer()
{
    // handle method call local.DataManager.fetchBtrLvFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchBtrLvFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

int DataManagerAdaptor::fetchHumFromServer()
{
    // handle method call local.DataManager.fetchHumFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchHumFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

int DataManagerAdaptor::fetchRpmFromServer()
{
    // handle method call local.DataManager.fetchRpmFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchRpmFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

int DataManagerAdaptor::fetchSpeedFromServer()
{
    // handle method call local.DataManager.fetchSpeedFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchSpeedFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

int DataManagerAdaptor::fetchTempFromServer()
{
    // handle method call local.DataManager.fetchTempFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchTempFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

void DataManagerAdaptor::saveBatteryLVInServer(int battery)
{
    // handle method call local.DataManager.saveBatteryLVInServer
    QMetaObject::invokeMethod(parent(), "saveBatteryLVInServer", Q_ARG(int, battery));
}

void DataManagerAdaptor::saveHumTempInServer(int hum, int temp)
{
    // handle method call local.DataManager.saveHumTempInServer
    QMetaObject::invokeMethod(parent(), "saveHumTempInServer", Q_ARG(int, hum), Q_ARG(int, temp));
}

void DataManagerAdaptor::saveRpmSpeedInServer(int rpm, int speed)
{
    // handle method call local.DataManager.saveRpmSpeedInServer
    QMetaObject::invokeMethod(parent(), "saveRpmSpeedInServer", Q_ARG(int, rpm), Q_ARG(int, speed));
}

