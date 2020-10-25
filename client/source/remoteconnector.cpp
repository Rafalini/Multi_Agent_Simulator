#include "../headers/remoteconnector.h"
#include <QJsonDocument>

RemoteConnector::RemoteConnector(MapProperties* map) : map(map), url(QStringLiteral("ws://127.0.0.1:1111")), connected(false)
{
    webSocket.open(url);
    connect(&webSocket, &QWebSocket::connected, this, &RemoteConnector::onConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &RemoteConnector::onDisconnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &RemoteConnector::onTextMessageReceived);
}

void RemoteConnector::submit() {
    QJsonDocument doc = map->toJson();
    qDebug() << "trying to send a message...";
    sendMessage(doc.toJson(QJsonDocument::Compact));
}

void RemoteConnector::sendMessage(QString message) {
    if(!connected)
        webSocket.open(url);
    else
        webSocket.sendTextMessage(message);
    qDebug() << "wasn't connected";
}
void RemoteConnector::onConnected()
{
    connected = true;
    qDebug() << "connected";

}

void RemoteConnector::onTextMessageReceived(QString message)
{
    qDebug() << "received a message: " << message;
    emit answerReceived(message);
}

void RemoteConnector::onDisconnected()
{
    connected = false;
    qDebug() << "disconnected";
}
