#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>

LineSegment::LineSegment(int id, Point* beg, Point* en, double len) : id(id), begining(beg), end(en), length(len) {}

int LineSegment::getId() const
{
    return id;
}

LineSegment::~LineSegment() {
    begining->removeSegment(this);
}

QJsonObject LineSegment::toJson() const {
    QJsonObject obj;
    obj["id"] = id;
    obj["x1"] = begining->getX();
    obj["y1"] = begining->getY();
    obj["x2"] = end->getX();
    obj["y2"] = end->getY();
    obj["length"] = length;
    return obj;
}
