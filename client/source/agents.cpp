#include "agents.h"
#include <QJsonArray>
#include <QJsonObject>

Agents::Agents(QObject *parent) : QAbstractListModel(parent){}

Agents::~Agents() {
    for(auto& agent : agents) {
        delete agent;
    }
}

void Agents::addAgentHistory(int index, const QJsonArray& history) {
    agents[index]->setHistory(history);
}

int Agents::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return agents.size();
}

QVariant Agents::data(const QModelIndex &index, int role) const { //unused role
    if (index.row() < 0 || index.row() >= agents.count())
        return QVariant();
    switch (role) {
        case BeginingRole:
        return QVariant::fromValue(agents[index.row()]->getBegining());
        break;
    case DestinationRole:
        return QVariant::fromValue(agents[index.row()]->getDestination());
        break;
    case LoadRole:
        return agents[index.row()]->getLoad();
        break;
    case AgentRole:
        return QVariant::fromValue(agents[index.row()]);
        break;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Agents::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[BeginingRole] = "begining";
    roles[DestinationRole] = "destination",
    roles[LoadRole] = "load";
    roles[AgentRole] = "agent";
    return roles;
}

void Agents::addAgent(City* begining, City* destination, double load) {
    if(destination == begining) {
        emit wrongAddAgentArguments("Miasto docelowe i początkowe muszą być różne");
        return;
    }
    if(load <= 0) {
        emit wrongAddAgentArguments("Ładunek musi być więc od 0");
        return;
    }
    Agent* newAgent = new Agent(begining, destination, load);
    auto lambda = [newAgent, this]() {
            QModelIndex index = QAbstractListModel::index(agents.indexOf(newAgent), 0);
            emit QAbstractListModel::dataChanged(index, index);
        };
    connect(newAgent, &Agent::beginingUpdated, this, lambda);
    connect(newAgent, &Agent::destinationUpdated, this, lambda);
    connect(newAgent, &Agent::loadUpdated, this, lambda);
    connect(newAgent, &Agent::cityDeleted, [this, newAgent]() {removeAgent(newAgent);});
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    agents.push_back(newAgent);
    endInsertRows();
}


QVector<Agent*> Agents::getAgents() const {
    return agents;
}

Agent* Agents::getAgent(const QModelIndex &index) {
    return agents[index.row()];
}

void Agents::removeAgent(Agent* agent) {
    int row = agents.indexOf(agent);
    beginRemoveRows(QModelIndex(), row, row);
    agents.removeOne(agent);
    endRemoveRows();
    delete agent;
}

QJsonArray Agents::toJson() const {
    QJsonArray array;
    for(const auto& agent : agents) {
        array.append(agent->tojSON());
    }
    return array;
}
