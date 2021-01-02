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

    MapProperties map;
    map.fill();

    //fill default agents
    Agents agents;
    agents.addAgent(map.getCities()[0], map.getCities()[1], 20);
    agents.addAgent(map.getCities()[2], map.getCities()[1], 22);
    agents.addAgent(map.getCities()[1], map.getCities()[2], 230);
    agents.addAgent(map.getCities()[2], map.getCities()[0], 2450);
    agents.addAgent(map.getCities()[1], map.getCities()[0], 265470);

    RemoteConnector remote(&map, &agents);

    engine.rootContext()->setContextProperty("remoteConnector", &remote);
    engine.rootContext()->setContextProperty("map", &map);
    engine.rootContext()->setContextProperty("agents", &agents);

    QQuickStyle::setStyle("Material");

    engine.load(url);
    return app.exec();
}
