#ifndef AGENTS_H
#define AGENTS_H

#include <QAbstractListModel>
#include <QObject>
#include <QDebug>
#include <QVector>
#include "agent.h"

class Agents : public QAbstractListModel
{
    Q_OBJECT
    enum AgentlRoles {
        BeginingRole = Qt::UserRole + 1,
        DestinationRole,
        LoadRole,
        CapacityRole,
        AgentRole
    };

public:
    explicit Agents(QObject *parent = nullptr);
    QJsonArray toJson() const ;
    Q_INVOKABLE void addAgent(City* start, City* destination, const double& load, const double& capacity);
    Q_INVOKABLE Agent* getAgent(const QModelIndex &index);
    Q_INVOKABLE void removeAgent(Agent*);
    Q_INVOKABLE QVector<Agent*> getAgents() const;
    Q_INVOKABLE int virtual rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE virtual QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE bool isCityUsed(City* city);
    void addAgentHistory(int index, const QJsonArray& history);
    void addAgentStatistics(int index, const QJsonObject& statistics);
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
