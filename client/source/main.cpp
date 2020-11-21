#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "../headers/remoteconnector.h"
#include "../headers/city.h"
#include "../headers/point.h"
#include "../headers/linesegment.h"
#include "../headers/mapproperties.h"
#include "../headers/agents.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qRegisterMetaType<Agent*>("Agent");
    qRegisterMetaType<Agents*>("Agents");
    qRegisterMetaType<City*>();
    qRegisterMetaType<QVector<City*>>();

    MapProperties map;
    map.addCity("Kraków", 0.55, 0.85);
    map.addCity("Warszawa", 0.65, 0.4);
    map.addPoint(0.1, 0.5);
    map.addPoint(0.5, 0.2);
    map.addSegment(100, map.getCities()[0], map.getPoints()[0]);
    map.addSegment(75, map.getCities()[0], map.getPoints()[1]);
    map.addSegment(80, map.getCities()[1], map.getPoints()[0]);
    map.addSegment(50, map.getCities()[1], map.getPoints()[1]);

    Agents agents;

    RemoteConnector remote(&map, &agents);

    engine.rootContext()->setContextProperty("remoteConnector", &remote);
    engine.rootContext()->setContextProperty("map", &map);
    engine.rootContext()->setContextProperty("agents", &agents);

    engine.load(url);
    return app.exec();
}
