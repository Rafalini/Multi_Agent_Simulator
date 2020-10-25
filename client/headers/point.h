#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <memory>
#include "linesegment.h"

class LineSegment; //forward declaration

class Point : public QObject
{
    Q_OBJECT
public:
    Point(double x, double y);
    virtual QJsonObject toJson();
    double getX() const;
    double getY() const;
    Q_INVOKABLE void addSegment(std::shared_ptr<LineSegment> seg);

protected:
    QVector<std::shared_ptr<LineSegment>> segments;
    double x;
    double y;
};

#endif // POINT_H
