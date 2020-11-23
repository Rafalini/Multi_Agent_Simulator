#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include "city.h"

class Agent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* destination READ getDestination);
    Q_PROPERTY(City* begining READ getBegining);
    Q_PROPERTY(double weight READ getWeight);

public:
    explicit Agent(QObject *parent = nullptr);
    QJsonObject tojSON() const;
    Agent(City* begining, City* destination, const double &weight);
    Q_INVOKABLE void update(City* start, City* dest, const double &weight);
    ~Agent();
    City* getBegining() const;
    City* getDestination() const;
    double getWeight() const;

signals:
    void edited();
    void deleted();

private:
    City* beginingCity;
    City* destinationCity;
    double weight;
};

#endif // AGENT_H
