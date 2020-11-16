#ifndef CITY_H
#define CITY_H

#include <QObject>
#include "point.h"


QT_FORWARD_DECLARE_CLASS(LineSegment); //forward declaration


class City : public Point
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name);

public:
    City(const QString& name, const double& x, const double& y);
    virtual QJsonObject toJson() const;

signals:

private:
    QString name;
};

#endif // CITY_H
