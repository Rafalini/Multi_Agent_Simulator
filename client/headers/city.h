#ifndef CITY_H
#define CITY_H

#include <QObject>
#include "point.h"

class City : public Point
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name);

public:
    City(QString name, double x, double y);
    virtual QJsonObject toJson() const;

signals:

private:
    QString name;
};

#endif // CITY_H
