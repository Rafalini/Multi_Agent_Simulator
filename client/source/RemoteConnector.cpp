#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "RemoteConnector.h"

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
    isGraphicalMode = parameters["isGraphical"].toBool();
    QJsonDocument doc(obj);
    sendMessage(doc.toJson(QJsonDocument::Compact));
}

void RemoteConnector::sendMessage(QString message) {
    if(!connected) {
        messageQueue.enqueue(message);
        webSocket.open(url);
    } else {
        qint64 numberOfBytesSent = webSocket.sendTextMessage(message);
        if(numberOfBytesSent == 0 || !connected) {
            messageQueue.enqueue(message);
            webSocket.open(url);
        }
    }
}

void RemoteConnector::onConnected() {
    connected = true;
    while(!messageQueue.isEmpty()) {
        QString message = messageQueue.dequeue();
        sendMessage(message);
    }
}

void RemoteConnector::onTextMessageReceived(QString message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(isGraphicalMode) {
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["agents"].toArray();
        QJsonArray arrPaths = obj["paths"].toArray();
        for(int i = 0; i < arrPaths.size(); ++i) {
            QJsonObject pathJson = arrPaths[i].toObject();
            int id = pathJson["path_id"].toString().toInt();
            pathJson.remove("path_id");
            Path* path = map->getPathById(id);
            path->setTrafficData(pathJson);
        }
        emit answerReceived();
        for(int i = 0; i < arr.size(); ++i) {
            QJsonObject agentData = arr[i].toObject();
            agents->addAgentHistory(i, agentData["history"].toArray());
            agents->addAgentStatistics(i, agentData["statistics"].toObject());
        }
        emit answerParsed();
    }
    else {
        QJsonArray arr = doc.array();
        for(int i = 0; i < arr.size(); ++i) {
            agents->addAgentStatistics(i, arr[i].toObject());
        }
        emit statisticsParsed();
    }
}

void RemoteConnector::onDisconnected() {
    connected = false;
    if(!messageQueue.isEmpty()) {
        webSocket.open(url);
    }
}
