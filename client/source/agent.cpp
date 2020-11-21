#include "../headers/agent.h"
#include <QJsonObject>

Agent::Agent(QObject *parent) : QObject(parent) {}

void Agent::update(const QString &begining, const QString &dest, const double &weight) {
    beginingCityName = begining;
    destinationCityName = dest;
    this->weight = weight;
    emit edited();
}

Agent::~Agent() {
    emit deleted();
}

QString Agent::getBegining() const
{
    return beginingCityName;
}

QString Agent::getDestination() const
{
    return destinationCityName;
}

double Agent::getWeight() const
{
    return weight;
}

QJsonObject Agent::tojSON() const {
    QJsonObject obj;
    obj["begining"] = beginingCityName;
    obj["destination"] = destinationCityName;
    obj["weight"] = weight;
    return obj;
}
