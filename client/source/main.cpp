#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "../headers/remoteconnector.h"
#include "../headers/city.h"
#include "../headers/point.h"
#include "../headers/linesegment.h"
#include "../headers/mapproperties.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    MapProperties map;
    map.addCity("Kraków", 10, 10);
    map.addCity("Warszawa", 20, 20);
    map.addPoint(10, 15);
    map.addPoint(15, 10);
    map.addSegment(100, map.getCities()[0], map.getPoints()[0]);
    map.addSegment(75, map.getCities()[0], map.getPoints()[1]);
    map.addSegment(80, map.getCities()[1], map.getPoints()[0]);
    map.addSegment(50, map.getCities()[1], map.getPoints()[1]);

    RemoteConnector remote(&map);

    engine.rootContext()->setContextProperty("remoteConnector", &remote);

    engine.load(url);
    return app.exec();
}
