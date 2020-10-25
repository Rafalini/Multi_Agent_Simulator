#ifndef CITY_H
#define CITY_H

#include <QObject>
#include "point.h"

class City : public Point
{
    Q_OBJECT
public:
    City(QString name, double x, double y);
    Q_PROPERTY(QString name MEMBER name);
    virtual QJsonObject toJson();
private:
    QString name;
};

#endif // CITY_H
