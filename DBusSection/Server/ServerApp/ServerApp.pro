QT -= gui

QT += core dbus

CONFIG += c++17 console
CONFIG -= app_bundle

DBUS_ADAPTORS += ../../interfaces/datamanager.xml

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cansocket.cpp \
        datamanager.cpp \
        main.cpp \
        printutils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cansocket.h \
    datamanager.h \
    printutils.h
