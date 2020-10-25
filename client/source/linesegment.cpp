#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>

LineSegment::LineSegment(int id, std::shared_ptr<Point> beg, std::shared_ptr<Point> en, double len) : id(id), begining(beg), end(en), length(len) {}

int LineSegment::getId() const
{
    return id;
}


QJsonObject LineSegment::toJson() {
    QJsonObject obj;
    obj["id"] = id;
    obj["x1"] = begining->getX();
    obj["y1"] = begining->getY();
    obj["x2"] = end->getX();
    obj["y2"] = end->getY();
    obj["length"] = length;
    return obj;
}
