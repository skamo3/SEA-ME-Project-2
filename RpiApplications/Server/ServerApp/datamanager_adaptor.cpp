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

int DataManagerAdaptor::fetchTempFromServer()
{
    // handle method call local.DataManager.fetchTempFromServer
    int out0;
    QMetaObject::invokeMethod(parent(), "fetchTempFromServer", Q_RETURN_ARG(int, out0));
    return out0;
}

void DataManagerAdaptor::saveCanDataInServer(const QDBusVariant &data)
{
    // handle method call local.DataManager.saveCanDataInServer
    QMetaObject::invokeMethod(parent(), "saveCanDataInServer", Q_ARG(QDBusVariant, data));
}
