#include <QJsonObject>
#include <QJsonArray>
#include "Point.h"
#include "City.h"

City::City(const QString& name, const double& x, const double& y) : Point(x, y), name(name) {}


City::City(const QString& name, const double& x, const double& y, const int& id) : Point(x, y, id), name(name) {}

QJsonObject City::toJson() const {
    QJsonObject obj = Point::toJson();
    obj["name"] = name;
    return obj;
}

const QString& City::getName() const {
    return name;
}

void City::setName(const QString& name) {
    if(this->name == name)
        return;
    this->name = name;
    emit nameChanged(name);
}
