#ifndef AGENTS_H
#define AGENTS_H

#include <QAbstractListModel>
#include <QObject>
#include <QDebug>
#include <QVector>
#include "mapproperties.h"
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
    explicit Agents(MapProperties* map, QObject *parent = nullptr);
    QJsonArray toJson() const ;
    void addAgentHistory(int index, const QJsonArray& history);
    void addAgentStatistics(int index, const QJsonObject& statistics);
    virtual ~Agents();
    void clear();
    void fill(QJsonDocument doc);
    Q_INVOKABLE void addAgent(City* start, City* destination, const double& load, const double& capacity);
    Q_INVOKABLE Agent* getAgent(const QModelIndex &index);
    Q_INVOKABLE void removeAgent(Agent*);
    Q_INVOKABLE QVector<Agent*> getAgents() const;
    Q_INVOKABLE int virtual rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE virtual QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE bool isCityUsed(City* city);
    Q_INVOKABLE void readFromJsonFile();
    Q_INVOKABLE void saveToJson();

signals:
    void agentsChanged();
    void agentChanged(Agent*);
    void agentAdded(Agent*);
    void wrongAddAgentArguments(QString);
    void fileFormatException();
    void noCityOfName(QString);

private:
    QVector<Agent*> agents;
    QString agentsJson = "[{\"begining\":\"Kraków\",\"capacity\":200,\"destination\":\"Warszawa\",\"id\":0,\"load\":20},{\"begining\":\"Szczecin\",\"capacity\":200,\"destination\":\"Warszawa\",\"id\":1,\"load\":22},{\"begining\":\"Warszawa\",\"capacity\":100,\"destination\":\"Szczecin\",\"id\":2,\"load\":230},{\"begining\":\"Szczecin\",\"capacity\":50,\"destination\":\"Kraków\",\"id\":3,\"load\":160},{\"begining\":\"Warszawa\",\"capacity\":500,\"destination\":\"Kraków\",\"id\":4,\"load\":200}]";
    MapProperties* map;
};

#endif // AGENTS_H
