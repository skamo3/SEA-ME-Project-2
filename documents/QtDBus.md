# How to use QDBus
- [Details and deeper information can check in official document](https://doc.qt.io/qt-5/qtdbus-index.html)

## Before the start
- Don't forget install DBus and execute DBus-daemon
- You can find it [here](git://anongit.freedesktop.org/git/dbus/dbus) or [here](https://www.freedesktop.org/wiki/Software/dbus/)

## To add a QDbus library to a pro file
- Add this line in .pro file
    ```
    QT += dbus
    ```

## Make object for communication

- Create a class that accepts data and stores it in variables
- [Using a previously used qmlController](./QtQmlCppMVC.md#qmlcontroller-class)
```c++
#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>

class QmlController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int data READ getData WRITE setData NOTIFY dataChanged)
public:
    explicit QmlController(QObject *parent = nullptr);

    int getData() const;
    void setData(int newData);

private:
    int data;

signals:
    void dataChanged();

public slots:
    // Add this function for DBus
    void increaseData();

};

#endif // QMLCONTROLLER_H

// define saveData in cpp file
void QmlController::increaseData()
{
    setData(data + 1);
}

```

### Conversion CPP to XML 
- Follow this command
    ```bash
    qdbuscpp2xml <filename>
    ```
- You can see this print
    ```

    ```
    - copy and make .xml file in directory name of **interfaces**
    - In this example, the name is qmlcontroller.xml

### Add Adaptor in .pro file
- Add this line in .pro file
```
DBUS_ADAPTORS += ../interfaces/qmlcontroller.xml
```
- When compile it will register Adaptor

## Register Server and contain object
- As above, add based on the main that you practiced before
```c++
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QmlController>("qml.data", 1, 0, "DataController");

    // make DBusConnection instance
    QDBusConnection connection = QDBusConnection::sessionBus();

    // check connection available
    if (!connection.isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    // declare object instance
    QmlController qmlController;

    // register object only slots
    connection.registerObject("/data", &qmlController, QDBusConnection::ExportAllSlots);

    // register service
    if (!connection.registerService("qml.server")) {
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }
    qDebug() << "DBus Server open";

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
```

## Change data in another application with QDbus

### Add Interfaces in .pro file
- Add this line in .pro file
```
DBUS_INTERFACES += ../interfaces/qmlcontroller.xml
```

### Simple code to change data in main
```c++
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    local::DataManager *dataManager = new local::DataManager("qml.server","/", QDBusConnection::sessionBus(), this);
    
    std::shared_ptr<class QTimer> Timer = std::make_shared<QTimer>();
    connect(Timer.get(), SIGNAL(timeout()), []() {
        dataManager->increaseData();
    });
    Timer->start(1000);

    return a.exec();
}
```
- Connect to DBus session
- Call Adaptor function with timer
- Set data to increase by 1 per second using Timer
