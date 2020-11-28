#ifndef CITY_H
#define CITY_H

#include <QObject>
#include "point.h"


QT_FORWARD_DECLARE_CLASS(LineSegment); //forward declaration


class City : public Point
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);

public:
    City(const QString& name, const double& x, const double& y);
    virtual QJsonObject toJson() const;
    const QString& getName() const;
    void setName(const QString& name);

signals:
    void nameChanged(QString);

private:
    QString name;
};

#endif // CITY_H
