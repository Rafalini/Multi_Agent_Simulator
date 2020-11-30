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
    agents.push_back(new Agent(begining, destination, load));
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
