#include "../headers/point.h"
#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>

Point::Point(double x, double y) : x(x), y(y) {}

void Point::addSegment(std::shared_ptr<LineSegment> seg) {
    segments.push_back(seg);
}

QJsonObject Point::toJson() {
    QJsonObject obj;
    obj["x"] = x;
    obj["y"] = y;
    QJsonArray segmentsArray;
    for(auto &segment : segments) {
        segmentsArray.append(segment->getId());
    }
    obj["segments"] = segmentsArray;
    return obj;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}
