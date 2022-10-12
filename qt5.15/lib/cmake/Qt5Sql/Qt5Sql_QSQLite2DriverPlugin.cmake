
add_library(Qt5::QSQLite2DriverPlugin MODULE IMPORTED)


_populate_Sql_plugin_properties(QSQLite2DriverPlugin RELEASE "sqldrivers/libqsqlite2.so" FALSE)

list(APPEND Qt5Sql_PLUGINS Qt5::QSQLite2DriverPlugin)
set_property(TARGET Qt5::Sql APPEND PROPERTY QT_ALL_PLUGINS_sqldrivers Qt5::QSQLite2DriverPlugin)
set_property(TARGET Qt5::QSQLite2DriverPlugin PROPERTY QT_PLUGIN_TYPE "sqldrivers")
set_property(TARGET Qt5::QSQLite2DriverPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::QSQLite2DriverPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QSQLite2DriverPlugin")
