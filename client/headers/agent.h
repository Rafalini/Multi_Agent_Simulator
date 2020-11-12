#ifndef AGENT_H
#define AGENT_H

#include <QObject>

class Agent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString destination MEMBER destinationCityName);
    Q_PROPERTY(QString begining MEMBER beginingCityName);
    Q_PROPERTY(double weight MEMBER weight)

public:
    explicit Agent(QObject *parent = nullptr);
    QJsonObject tojSON() const;
    Agent(const QString& begining, const QString& dest, const double& weight) : beginingCityName(begining), destinationCityName(dest), weight(weight) {}
    Q_INVOKABLE void update(const QString& start, const QString& dest, const double& weight);
    ~Agent();

signals:
    void edited();
    void deleted();

private:
    QString beginingCityName;
    QString destinationCityName;
    double weight;
};

#endif // AGENT_H
