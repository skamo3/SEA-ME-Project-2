QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

_ROOT = $$_PRO_FILE_PWD_
INCLUDEPATH += $$_ROOT/../../Server/src-gen

SOURCES += \
        datacontroller.cpp \
        main.cpp

RESOURCES += qml.qrc \
    components/components.qrc \
    images/images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    datacontroller.h

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Server/libraries/capicxx-core-runtime/build/release/ -lCommonAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Server/libraries/capicxx-core-runtime/build/debug/ -lCommonAPI
else:unix: LIBS += -L$$PWD/../../Server/libraries/capicxx-core-runtime/build/ -lCommonAPI

INCLUDEPATH += $$PWD/../../Server/libraries/capicxx-core-runtime/include
DEPENDPATH += $$PWD/../../Server/libraries/capicxx-core-runtime/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Server/libraries/capicxx-dbus-runtime/build/release/ -lCommonAPI-DBus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Server/libraries/capicxx-dbus-runtime/build/debug/ -lCommonAPI-DBus
else:unix: LIBS += -L$$PWD/../../Server/libraries/capicxx-dbus-runtime/build/ -lCommonAPI-DBus

INCLUDEPATH += $$PWD/../../Server/libraries/capicxx-dbus-runtime/include
DEPENDPATH += $$PWD/../../Server/libraries/capicxx-dbus-runtime/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Server/libraries/dbus-1.10.10/dbus/.libs/release/ -ldbus-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Server/libraries/dbus-1.10.10/dbus/.libs/debug/ -ldbus-1
else:unix: LIBS += -L$$PWD/../../Server/libraries/dbus-1.10.10/dbus/.libs/ -ldbus-1

INCLUDEPATH += $$PWD/../../Server/libraries/dbus-1.10.10/dbus
DEPENDPATH += $$PWD/../../Server/libraries/dbus-1.10.10/dbus
