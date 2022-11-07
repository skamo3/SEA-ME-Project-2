# QT use Qml file and C++ 
- There are various ways to transfer data from qml to C++

```c++
SampleModel Model;
engine.rootContext()->setContextProperty("ModelName", &Model);
```
- Basically, there is a way to register the model at the root of the engine in the same way as above, but if the program grows, all qml will load that object.

# MVC Model & MVVM Model

## MVC Model
- Model - View - Controller
    - Controller. Change the status of a model by sending commands to the model
    - Model. Send changes to Controller and View
    - View. Obtain information from the Model to displayable results for the user to view
- [Detail of MVC Model](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller)

## MVVM Model
- Model - View - ViewModel
    - ViewModel acts as a model from a View perspective and View from a Model perspective
    - MVC models have a dependency between View and Model, while MVVM models have no dependency between View and Model, enabling modularity

# Use MVVM Model in Qt qml and C++

## C++ Main
```c++
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QmlController>("qml.data", 1, 0, "DataController");

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
- line36. Register QmlController class as Component to handle qml data
### qmlRegisterType  
```c++
template<typename T>
int qmlRegisterType(const char *uri, int versionMajor, int versionMinor, const char *qmlName);
```
- This template function registers the C++ type in the QML system with the **name** qmlName, in the library imported from **uri** having the version number composed from versionMajor and versionMinor.
- Return. QML type id
- [Detail of qmlRegisterType](https://doc.qt.io/qt-6/qqmlengine.html#qmlRegisterType)

## QmlController class

- qmlController.h
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

    };

    #endif // QMLCONTROLLER_H
    ```
- qmlDatacontroller.cpp
    - Must to call signal function in setter 
    ```c++
    void QmlController::setData(int newData)
    {
        if (data == newData) // if values are same. just return
            return;
        data = newData; // save data
        emit dataChanged(); // call signal. qml never update value without this 
    }
    ```


## Call C++ instance in qml

```xml
import QtQuick 2.15
import QtQuick.Window 2.15
import qml.data 1.0

Window {
    width: 1024
    height: 600
    visible: true
    title: qsTr("Hello World")
    DataController {
        id: qmlDataController
    }

    Rectangle {
        id: testRectangle
        width: height
        height: parent.height / 3
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#003318"
        Text {
            id: testText
            text: qmlDataController.data
            font.pointSize: 80
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    
}
```

- Put the variable into the properties of the part to which you want to apply the data
- In the example, the component is imported from the main.qml, but in the actual code, the component can be imported into the corresponding qml

> Warning
> - Even if the same component is called from a different qml file, it may not be updated
> - ex) Data.qml Button.qml If you have these two files, clicking Button in Button.qml may not change the value inside Data.qml. Don't forget when doing the test.