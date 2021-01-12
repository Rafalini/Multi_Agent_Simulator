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

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    MapProperties map;

    //fill default agents
    Agents agents(&map);
    //clear all agents if map needs to be cleared
    QObject::connect(&map, &MapProperties::aboutToClear, &agents, &Agents::clear);

    RemoteConnector remote(&map, &agents);
    engine.rootContext()->setContextProperty("remoteConnector", &remote);
    engine.rootContext()->setContextProperty("map", &map);
    engine.rootContext()->setContextProperty("agents", &agents);

    QQuickStyle::setStyle("Material");
    qmlRegisterUncreatableType<Path>("MultiAgentSimulator", 1, 0,  "RoadType", "Error: only enums");
    engine.load(url);
    return app.exec();
}
