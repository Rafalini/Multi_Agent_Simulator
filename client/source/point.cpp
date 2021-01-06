#include <QJsonObject>
#include <QJsonArray>
#include "path.h"
#include "point.h"

Point::Point(const double& x, const double& y, const int& id) : id(id) {
    setX(x);
    setY(y);
}

void Point::setX(const double& x) {
    if(x == this->x) return;
    if(x<0) {
        this->x = 0;
    }else if(x > 1) {
        this->x = 1;
    } else {
        this->x = x;
    }
    emit xChanged(this->x);
}

QVector<Path*> Point::getPaths() const {
    return paths;
}

void Point::setY(const double& y) {
    if(y == this->y) return;
    if(y<0) {
        this->y = 0;
    }else if(y > 1) {
        this->y = 1;
    } else {
        this->y = y;
    }
    emit yChanged(this->y);
}

void Point::addPath(Path* path) {
    paths.push_back(path);
}

void Point::removePath(Path* path) {
    paths.removeOne(path);
}

QJsonObject Point::toJson() const {
    QJsonObject obj;
    obj["x"] = x;
    obj["y"] = y;
    obj["id"] = id;
    return obj;
}

int Point::getId() const
{
    return id;
}

const double& Point::getX() const
{
    return x;
}

const double& Point::getY() const
{
    return y;
}
