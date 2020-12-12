#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "remoteconnector.h"
#include "city.h"
#include "point.h"
#include "path.h"
#include "mapproperties.h"
#include "agents.h"

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

    qRegisterMetaType<Agent*>("Agent*");
    qRegisterMetaType<Agents*>("Agents*");
    qRegisterMetaType<City*>("City*");
    qRegisterMetaType<Point*>("Point*");
    qRegisterMetaType<Path*>("Path*");
    qRegisterMetaType<QVector<City*>>();

    MapProperties map;
    map.addCity("Kraków", 0.55, 0.85);
    map.addCity("Warszawa", 0.65, 0.4);
    map.addCity("Szczecin", 0.1, 0.12);
    map.addPoint(0.1, 0.5);
    map.addPoint(0.5, 0.7);
    map.addPath(map.getCities()[0], map.getPoints()[0]);
    map.addPath(map.getCities()[0], map.getPoints()[1]);
    map.addPath(map.getCities()[1], map.getPoints()[0]);
    map.addPath(map.getCities()[1], map.getPoints()[1]);
    map.addPath(map.getCities()[2], map.getPoints()[0]);
    map.addPath(map.getCities()[2], map.getCities()[1]);

    Agents agents;

    RemoteConnector remote(&map, &agents);

    engine.rootContext()->setContextProperty("remoteConnector", &remote);
    engine.rootContext()->setContextProperty("map", &map);
    engine.rootContext()->setContextProperty("agents", &agents);

    QQuickStyle::setStyle("Material");

    engine.load(url);
    return app.exec();
}
