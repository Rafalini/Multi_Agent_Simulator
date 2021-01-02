#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QJsonArray>
#include "city.h"
#include "point.h"

class Agent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* destination READ getDestination WRITE setDestination NOTIFY destinationUpdated);
    Q_PROPERTY(City* begining READ getBegining WRITE setBegining NOTIFY beginingUpdated);
    Q_PROPERTY(QJsonArray history READ getHistory WRITE setHistory NOTIFY historyUpdated);
    Q_PROPERTY(double load READ getLoad WRITE setLoad NOTIFY loadUpdated);

public:
    explicit Agent(QObject *parent = nullptr);
    QJsonObject tojSON() const;
    Agent(City* begining, City* destination, const double &load);
    City* getBegining() const;
    City* getDestination() const;
    double getLoad() const;
    void setBegining(City* beg);
    void setDestination(City* dest);
    void setHistory(const QJsonArray& history);
    void setLoad(const double& load);
    Q_INVOKABLE void update(City* beg, City* dest, const double &load);
    virtual ~Agent();
    QJsonArray getHistory() const;

signals:
    void destinationUpdated();
    void beginingUpdated();
    void loadUpdated();
    void deleted();
    void wrongUpdateArguments(const QString&);
    void cityDeleted();
    void historyUpdated();

private:
    City* beginingCity;
    City* destinationCity;
    double load;
    QJsonArray history;
};

#endif // AGENT_H
