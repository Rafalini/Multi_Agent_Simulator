#include "../headers/agents.h"
#include <QJsonArray>
#include <QJsonObject>

Agents::Agents(QObject *parent) : QObject(parent){}

Agents::~Agents() {
    for(auto& agent : agents) {
        delete agent;
    }
}

void Agents::addAgent(QString start, QString destination, double weight) {
    agents.push_back(new Agent(start, destination, weight));
    emit agentAdded(agents.last());
}

Agent* Agents::getAgent(int agentId) {
    return agents[agentId];
}

void Agents::removeAgent(Agent* agent) {
    agents.removeOne(agent);
    delete agent;
}

QJsonObject Agents::toJson() const {
    QJsonArray array;
    for(const auto& agent : agents) {
        array.append(agent->tojSON());
    }
    QJsonObject obj;
    obj["agents"] = array;
    return obj;
}
