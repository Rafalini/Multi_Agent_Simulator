#include "../headers/agents.h"
#include <QJsonArray>
#include <QJsonObject>

Agents::Agents(QObject *parent) : QObject(parent){}

Agents::~Agents() {
    for(auto& agent : agents) {
        delete agent;
    }
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
    agents.push_back(newAgent);
    emit agentAdded(newAgent);
}


QVector<Agent*> Agents::getAgents() const {
    return agents;
}

Agent* Agents::getAgent(int agentId) {
    return agents[agentId];
}

void Agents::removeAgent(Agent* agent) {
    agents.removeOne(agent);
    delete agent;
}

QJsonArray Agents::toJson() const {
    QJsonArray array;
    for(const auto& agent : agents) {
        array.append(agent->tojSON());
    }
    return array;
}
