#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "datacontroller.h"

#include <QtDBus/QtDBus>


int main(int argc, char *argv[])
{
#if QT_VERSIODataN < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    QDBusInterface iface("org.example.QtDBus.PingExample", "/", "", QDBusConnection::sessionBus());
    qDebug() << "test";
    if (iface.isValid()) {
        QDBusReply<QString> reply = iface.call("ping", argc > 1 ? argv[1] : "");
        if (reply.isValid()) {
            printf("Reply was: %s\n", qPrintable(reply.value()));
        } else {
            fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
            return 1;
        }

    }

    DataController controller;

    engine.rootContext()->setContextProperty("DataController", &controller);
    engine.load(url);

    return app.exec();
}
