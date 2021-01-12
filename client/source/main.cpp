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
    map.fill();

    //fill default agents
    Agents agents;
    auto cities = map.getCities();
    agents.addAgent(cities[0], cities[1], 20, 200);
    agents.addAgent(cities[2], cities[1], 22, 200);
    agents.addAgent(cities[1], cities[2], 230, 100);
    agents.addAgent(cities[2], cities[0], 160, 50);
    agents.addAgent(cities[1], cities[0], 200, 500);

    RemoteConnector remote(&map, &agents);

    engine.rootContext()->setContextProperty("remoteConnector", &remote);
    engine.rootContext()->setContextProperty("map", &map);
    engine.rootContext()->setContextProperty("agents", &agents);

    QQuickStyle::setStyle("Material");
    qmlRegisterUncreatableType<Path>("MultiAgentSimulator", 1, 0,  "RoadType", "Error: only enums");
    engine.load(url);
    return app.exec();
}
