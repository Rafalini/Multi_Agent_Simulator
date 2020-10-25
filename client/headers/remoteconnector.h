#ifndef REMOTECONNECTOR_H
#define REMOTECONNECTOR_H
#include <QObject>
#include "mapproperties.h"
#include <QtWebSockets>


class RemoteConnector : public QObject
{
    Q_OBJECT
public:
    RemoteConnector(MapProperties *map);
    Q_INVOKABLE void submit();
signals:
    void answerReceived(QString);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();

private:
    void sendMessage(QString message);
    MapProperties *map;
    QWebSocket webSocket;
    QUrl url;
    bool connected;
};

#endif // REMOTECONNECTOR_H
