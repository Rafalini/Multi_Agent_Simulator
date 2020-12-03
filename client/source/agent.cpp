#include "../headers/agent.h"
#include <QJsonObject>

Agent::Agent(QObject *parent) : QObject(parent) {}

Agent::Agent(City* begining, City* destination, const double &weight) : beginingCity(begining), destinationCity(destination), load(weight) {}

Agent::~Agent() {
    emit deleted();
}

void Agent::update(City* begining, City* destination, const double &load) {
    if(load <= 0) {
        emit wrongUpdateArguments("Waga nie może być mniejsza od 0");
        return;
    }

    if(destination == nullptr || begining == nullptr) {
        emit wrongUpdateArguments("Miasto nie może być puste");
        return;
    }

    if(destination == begining) {
        emit wrongUpdateArguments("Miasto docelowe i początkowe muszą być różne");
        return;
    }

    this->load = load;
    emit loadUpdated();

    if(destination == beginingCity && begining == destinationCity) {
        City* swap = beginingCity;
        beginingCity = destinationCity;
        destinationCity = swap;
        emit destinationUpdated();
        emit beginingUpdated();
        return;
    }
    setBegining(begining);
    setDestination(destination);
}


void Agent::setBegining(City* beg) {
    if(beg == nullptr) {
        emit wrongUpdateArguments("Miasto nie może być puste");
        return;
    }
    this->beginingCity = beg;
    emit beginingUpdated();

}
void Agent::setDestination(City* dest) {
    if(dest == nullptr) {
        emit wrongUpdateArguments("Miasto nie może być puste");
        return;
    }
    this->destinationCity = dest;
    emit destinationUpdated();
}

void Agent::setLoad(const double& load) {
    if(load <= 0) {
        emit wrongUpdateArguments("Waga nie może być mniejsza od 0");
        return;
    }
    this->load = load;
    emit loadUpdated();
}

City* Agent::getBegining() const
{
    return beginingCity;
}

City* Agent::getDestination() const
{
    return destinationCity;
}

double Agent::getLoad() const
{
    return load;
}

QJsonObject Agent::tojSON() const {
    QJsonObject obj;
    obj["begining"] = beginingCity->getName();
    obj["destination"] = destinationCity->getName();
    obj["load"] = load;
    return obj;
}
