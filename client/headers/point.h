#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <memory>
#include "linesegment.h"

class LineSegment; //forward declaration

class Point : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x MEMBER x);
    Q_PROPERTY(double y MEMBER y);

public:
    Point(const double& x, const double& y);
    const double& getX() const;
    const double& getY() const;
    Q_INVOKABLE void addSegment(LineSegment* seg);
    Q_INVOKABLE void removeSegment(LineSegment* seg);
    virtual QJsonObject toJson() const;

protected:
    QVector<LineSegment*> segments;
    double x;
    double y;
};

#endif // POINT_H
