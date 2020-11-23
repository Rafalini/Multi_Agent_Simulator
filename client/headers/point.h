#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <QVector>
#include "linesegment.h"

QT_FORWARD_DECLARE_CLASS(LineSegment); //forward declaration
//Class representing a point on map, where roads can split or merge, the coordinates are within range (0,1)
class Point : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ getX WRITE setX FINAL);
    Q_PROPERTY(double y READ getY WRITE setY FINAL);

public:
    Point(const double& x, const double& y);
    const double& getX() const;
    const double& getY() const;
    Q_INVOKABLE void setX(const double& x);
    Q_INVOKABLE void setY(const double& y);
    Q_INVOKABLE void addSegment(LineSegment* seg);
    Q_INVOKABLE void removeSegment(LineSegment* seg);
    virtual QJsonObject toJson() const;

protected:
    QVector<LineSegment*> segments;
    double x;
    double y;
};

#endif // POINT_H
