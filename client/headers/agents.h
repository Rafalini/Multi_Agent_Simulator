#ifndef AGENTS_H
#define AGENTS_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include "agent.h"

class Agents : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<Agent*> agents MEMBER agents);

public:
    explicit Agents(QObject *parent = nullptr);
    QJsonObject toJson() const ;
    Q_INVOKABLE void addAgent(QString start, QString destination, double weight);
    Q_INVOKABLE Agent* getAgent(int agentId);
    Q_INVOKABLE void removeAgent(Agent* agent);
    ~Agents();

signals:
    void agentAdded(Agent*);
    void agentChanged(Agent*);
    void agentDeleted(Agent*);

private:
    QVector<Agent*> agents;
};

#endif // AGENTS_H
