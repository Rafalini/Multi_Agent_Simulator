#ifndef REMOTECONNECTOR_H
#define REMOTECONNECTOR_H
#include <QObject>
#include <QWebSocket> //"qwebsocket.h"
#include <QQueue>
#include <QJsonObject>
#include "mapproperties.h"
#include "agents.h"

class RemoteConnector : public QObject
{
    Q_OBJECT

public:
    RemoteConnector(MapProperties *map, Agents* agents);
    Q_INVOKABLE void submit();

signals:
    void answerReceived();
    void addAgentRepresentation(QJsonObject);
    void answerParsed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();

private:
    void sendMessage(QString message);
    MapProperties* map;
    Agents* agents;
    QWebSocket webSocket;
    QUrl url;
    bool connected;
    QQueue<QString> messageQueue;
};

#endif // REMOTECONNECTOR_H
