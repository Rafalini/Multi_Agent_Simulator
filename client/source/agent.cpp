#include "../headers/agent.h"
#include <QJsonObject>

Agent::Agent(QObject *parent) : QObject(parent) {}

Agent::Agent(City* begining, City* destination, const double &weight) : beginingCity(begining), destinationCity(destination), weight(weight) {}

void Agent::update(City* begining, City* destination, const double &weight) {
    if(weight <= 0) {
        emit wrongUpdateArguments("Waga nie może być mniejsza od 0");
        return;
    }
    if(begining != beginingCity || destination != destinationCity || weight != this->weight) {
        beginingCity = begining;
        destinationCity = destination;
        this->weight = weight;
        emit updated();
    }
}

Agent::~Agent() {
    emit deleted();
}

City* Agent::getBegining() const
{
    return beginingCity;
}

City* Agent::getDestination() const
{
    return destinationCity;
}

double Agent::getWeight() const
{
    return weight;
}

QJsonObject Agent::tojSON() const {
    QJsonObject obj;
    obj["begining"] = beginingCity->getName();
    obj["destination"] = destinationCity->getName();
    obj["weight"] = weight;
    return obj;
}
