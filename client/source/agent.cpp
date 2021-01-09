#include "agent.h"
#include <QJsonObject>

int Agent::next_id = 0;

Agent::Agent(QObject *parent) : QObject(parent) {}

Agent::Agent(City* begining, City* destination, const double &load, const double &capacity) : beginingCity(begining), destinationCity(destination),  id(next_id++), load(load), capacity(capacity) {
    connect(destinationCity, &City::deleted, this, &Agent::cityDeleted);
    connect(beginingCity, &City::deleted, this, &Agent::cityDeleted);
}

Agent::~Agent() {
    emit deleted();
}

QJsonArray Agent::getHistory() const {
    return history;
}

double Agent::getCapacity() const
{
    return capacity;
}

void Agent::setCapacity(double value)
{
    capacity = value;
    emit capacityUpdated();
}

int Agent::getId() const
{
    return id;
}

QJsonObject Agent::getStatistics() const
{
    return statistics;
}

void Agent::setStatistics(const QJsonObject &value)
{
    statistics = value;
}

void Agent::setHistory(const QJsonArray &history) {
    this->history = history;
    emit historyUpdated();
}

void Agent::update(City* begining, City* destination, const double &load, const double &capacity) {
    if(load <= 0) {
        emit wrongUpdateArguments("Waga ładunki nie może być mniejsza od 0");
        return;
    }

    if(capacity <= 0) {
        emit wrongUpdateArguments("Ładowność nie może być mniejsza od 0");
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

    this->capacity = capacity;
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
    disconnect(beginingCity, &City::deleted, this, &Agent::cityDeleted);
    this->beginingCity = beg;
    connect(beginingCity, &City::deleted, this, &Agent::cityDeleted);
    emit beginingUpdated();

}
void Agent::setDestination(City* dest) {
    if(dest == nullptr) {
        emit wrongUpdateArguments("Miasto nie może być puste");
        return;
    }
    disconnect(destinationCity, &City::deleted, this, &Agent::cityDeleted);
    this->destinationCity = dest;
    connect(destinationCity, &City::deleted, this, &Agent::cityDeleted);
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

City* Agent::getBegining() const {
    return beginingCity;
}

City* Agent::getDestination() const {
    return destinationCity;
}

double Agent::getLoad() const {
    return load;
}

QJsonObject Agent::tojSON() const {
    QJsonObject obj;
    obj["begining"] = beginingCity->getName();
    obj["destination"] = destinationCity->getName();
    obj["load"] = load;
    obj["capacity"] = capacity;
    obj["id"] = id;
    return obj;
}
