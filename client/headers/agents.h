#ifndef AGENTS_H
#define AGENTS_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include "agent.h"

class Agents : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<Agent*> agents READ getAgents);

public:
    explicit Agents(QObject *parent = nullptr);
    QJsonArray toJson() const ;
    Q_INVOKABLE void addAgent(City* start, City* destination, double weight);
    Q_INVOKABLE Agent* getAgent(int agentId);
    Q_INVOKABLE void removeAgent(Agent* agent);
    Q_INVOKABLE QVector<Agent*> getAgents() const;
    ~Agents();

signals:
    void agentsChanged();
    void agentChanged(Agent*);
    void agentAdded(Agent*);
    void wrongAddAgentArguments(QString);

private:
    QVector<Agent*> agents;
};

#endif // AGENTS_H
