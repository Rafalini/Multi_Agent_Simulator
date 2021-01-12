#include "agents.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>

Agents::Agents(MapProperties* map, QObject *parent) : QAbstractListModel(parent), map(map) {
    QJsonDocument doc =  QJsonDocument::fromJson(agentsJson.toUtf8());
    fill(doc);
}

Agents::~Agents() {
    for(auto& agent : agents) {
        delete agent;
    }
}

void Agents::clear() {
    beginRemoveRows(QModelIndex(), 0, agents.size());
    while(!agents.isEmpty()) {
        Agent* agent = agents[agents.size()-1];
        agents.removeOne(agent);
        agent->deleteLater();
    }
    endRemoveRows();
}

void Agents::saveToJson() {
    QJsonArray agentsJson = toJson();
    QJsonDocument doc;
    doc.setArray(agentsJson);
    QDateTime current_date = QDateTime::currentDateTime();
    QString date = current_date.toString("yyyy-MM-dd-hh-mm-ss");
    QString fileName = "agenci"+date+".json";
    QFileDialog::saveFileContent(doc.toJson(), fileName.toUtf8());
}

void Agents::readFromJsonFile() {
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (!fileName.isEmpty()) {
            QJsonDocument doc = QJsonDocument::fromJson(fileContent);
            if(doc.toJson() == "") {
                emit fileFormatException();
                return;
            }
            clear();
            fill(doc);
            emit readFromFileFinished();
        }
    };
    QFileDialog::getOpenFileContent("Pliki (*.txt *.json)",  fileContentReady);
}

void Agents::fill(QJsonDocument doc) {
    if(agents.size() > 0) return;
    QJsonArray agents_ = doc.array();
    for(int i = 0; i < agents_.size(); ++i) {
        QJsonObject agent = agents_[i].toObject();
        City * begining = map->getCityByName(agent["begining"].toString());
        if(begining == nullptr) {
            emit noCityOfName(agent["begining"].toString());
            continue;
        }
        City * destination = map->getCityByName(agent["destination"].toString());
        if(destination == nullptr) {
            emit noCityOfName(agent["begining"].toString());
            continue;
        }
        double load = agent["load"].toDouble();
        double capacity = agent["capacity"].toDouble();
        addAgent(begining, destination, load, capacity);
    }
}


void Agents::addAgentHistory(int index, const QJsonArray& history) {
    agents[index]->setHistory(history);
}

void Agents::addAgentStatistics(int index, const QJsonObject &statistics) {
    agents[index]->setStatistics(statistics);
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
    case CapacityRole:
        return agents[index.row()]->getCapacity();
        break;
    case AgentRole:
        return QVariant::fromValue(agents[index.row()]);
        break;
    default:
        return QVariant();
    }
}

bool Agents::isCityUsed(City *city) {
    for(auto agent : agents) {
        if(agent->getBegining() == city || agent->getDestination() == city)
            return true;
    }
    return false;
}

QHash<int, QByteArray> Agents::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[BeginingRole] = "begining";
    roles[DestinationRole] = "destination",
    roles[LoadRole] = "load";
    roles[CapacityRole] = "capacity";
    roles[AgentRole] = "agent";
    return roles;
}

void Agents::addAgent(City* begining, City* destination, const double& load, const double& capacity) {
    if(destination == begining) {
        emit wrongAddAgentArguments("Miasto docelowe i początkowe muszą być różne");
        return;
    }
    if(load <= 0) {
        emit wrongAddAgentArguments("Ładunek musi być większy od 0");
        return;
    }
    if(capacity <= 0) {
        emit wrongAddAgentArguments("Ładowność musi być większa od 0");
        return;
    }
    Agent* newAgent = new Agent(begining, destination, load, capacity);
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
