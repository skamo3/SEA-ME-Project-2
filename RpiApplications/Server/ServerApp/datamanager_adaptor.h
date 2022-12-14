/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -a datamanager_adaptor.h: ../../interfaces/datamanager.xml
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DATAMANAGER_ADAPTOR_H
#define DATAMANAGER_ADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface local.DataManager
 */
class DataManagerAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.DataManager")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"local.DataManager\">\n"
"    <signal name=\"broadRpmSpeedChanged\"/>\n"
"    <signal name=\"broadHumTempChanged\"/>\n"
"    <signal name=\"broadBatteryChanged\"/>\n"
"    <method name=\"saveRpmSpeedInServer\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"rpm\"/>\n"
"      <arg direction=\"in\" type=\"i\" name=\"speed\"/>\n"
"    </method>\n"
"    <method name=\"saveHumTempInServer\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"hum\"/>\n"
"      <arg direction=\"in\" type=\"i\" name=\"temp\"/>\n"
"    </method>\n"
"    <method name=\"saveBatteryLVInServer\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"battery\"/>\n"
"    </method>\n"
"    <method name=\"fetchRpmFromServer\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"    <method name=\"fetchTempFromServer\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"    <method name=\"fetchHumFromServer\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"    <method name=\"fetchBtrLvFromServer\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"    <method name=\"fetchSpeedFromServer\">\n"
"      <arg direction=\"out\" type=\"i\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    DataManagerAdaptor(QObject *parent);
    virtual ~DataManagerAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    int fetchBtrLvFromServer();
    int fetchHumFromServer();
    int fetchRpmFromServer();
    int fetchSpeedFromServer();
    int fetchTempFromServer();
    void saveBatteryLVInServer(int battery);
    void saveHumTempInServer(int hum, int temp);
    void saveRpmSpeedInServer(int rpm, int speed);
Q_SIGNALS: // SIGNALS
    void broadBatteryChanged();
    void broadHumTempChanged();
    void broadRpmSpeedChanged();
};

#endif
