#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "remoteconnector.h"

RemoteConnector::RemoteConnector(MapProperties* map, Agents* agents) : map(map), agents(agents), url(QStringLiteral("ws://127.0.0.1:1111")), connected(false)
{
    webSocket.open(url);
    connect(&webSocket, &QWebSocket::connected, this, &RemoteConnector::onConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &RemoteConnector::onDisconnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &RemoteConnector::onTextMessageReceived);
}

void RemoteConnector::submit(const QJsonObject& parameters) {
    QJsonObject obj;
    obj["map"] = map->toJson();
    obj["agents"] = agents->toJson();
    obj["parameters"] = parameters;
    QJsonDocument doc(obj);
    qDebug() << "trying to send a message...";
    sendMessage(doc.toJson(QJsonDocument::Compact));
}

void RemoteConnector::sendMessage(QString message) {
    if(!connected) {
        messageQueue.enqueue(message);
        webSocket.open(url);
    } else {
        qint64 numberOfBytesSent = webSocket.sendTextMessage(message);
        if(numberOfBytesSent == 0 && !connected) {
            messageQueue.enqueue(message);
            webSocket.open(url);
        }
    }
}

void RemoteConnector::onConnected() {
    connected = true;
    qDebug() << "connected";
    while(!messageQueue.isEmpty()) {
        QString message = messageQueue.dequeue();
        sendMessage(message);
    }
}

void RemoteConnector::onTextMessageReceived(QString message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonArray arr = doc.array();
    emit answerReceived();
    for(int i = 0; i < arr.size(); ++i) {
        QJsonObject agentData = arr[i].toObject();
        agents->addAgentHistory(i, agentData["history"].toArray());
//        agents->addStatistics(i, agentData["statistics"].toObject());
    }
    emit answerParsed();
}

void RemoteConnector::onDisconnected() {
    connected = false;
    qDebug() << "disconnected";
}
