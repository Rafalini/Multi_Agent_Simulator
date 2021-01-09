#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include "city.h"
#include "point.h"

class Agent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* destination READ getDestination WRITE setDestination NOTIFY destinationUpdated);
    Q_PROPERTY(City* begining READ getBegining WRITE setBegining NOTIFY beginingUpdated);
    Q_PROPERTY(QJsonArray history READ getHistory WRITE setHistory NOTIFY historyUpdated);
    Q_PROPERTY(QJsonObject statistics READ getStatistics WRITE setStatistics NOTIFY statisticsUpdated);
    Q_PROPERTY(double load READ getLoad WRITE setLoad NOTIFY loadUpdated);
    Q_PROPERTY(double capacity READ getCapacity WRITE setCapacity NOTIFY capacityUpdated);
    Q_PROPERTY(int id READ getId NOTIFY idUpdated);

public:
    explicit Agent(QObject *parent = nullptr);
    QJsonObject tojSON() const;
    Agent(City* begining, City* destination, const double &load, const double &capacity);
    City* getBegining() const;
    City* getDestination() const;
    double getLoad() const;
    void setBegining(City* beg);
    void setDestination(City* dest);
    void setHistory(const QJsonArray& history);
    void setStatistics(const QJsonObject &value);
    QJsonObject getStatistics() const;
    void setLoad(const double& load);
    Q_INVOKABLE void update(City* beg, City* dest, const double &load, const double &capacity);
    virtual ~Agent();
    QJsonArray getHistory() const;
    double getCapacity() const;
    void setCapacity(double value);
    int getId() const;

signals:
    void destinationUpdated();
    void beginingUpdated();
    void loadUpdated();
    void capacityUpdated();
    void deleted();
    void wrongUpdateArguments(const QString&);
    void cityDeleted();
    void historyUpdated();
    void statisticsUpdated();
    void idUpdated();

private:
    City* beginingCity;
    City* destinationCity;
    int id;
    double load;
    double capacity;
    QJsonArray history;
    QJsonObject statistics;
    static int next_id;
};

#endif // AGENT_H
