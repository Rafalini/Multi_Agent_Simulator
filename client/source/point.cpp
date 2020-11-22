#include "../headers/point.h"
#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>

Point::Point(const double& x, const double& y) : x(x), y(y) {
    segments = new QVector<LineSegment*>();
}

void Point::addSegment(LineSegment* seg) {
    segments->push_back(seg);
}

void Point::removeSegment(LineSegment* seg) {
    segments->removeOne(seg);
}

QJsonObject Point::toJson() const {
    QJsonObject obj;
    obj["x"] = x;
    obj["y"] = y;
    QJsonArray segmentsArray;
    for(auto &segment : *segments) {
        segmentsArray.append(segment->getId());
    }
    obj["segments"] = segmentsArray;
    return obj;
}


const double& Point::getX() const
{
    return x;
}

const double& Point::getY() const
{
    return y;
}
