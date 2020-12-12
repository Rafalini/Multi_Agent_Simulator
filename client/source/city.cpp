#include "point.h"
#include "city.h"
#include <QJsonObject>
#include <QJsonArray>

City::City(const QString& name, const double& x, const double& y) : Point(x, y), name(name) {}

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
