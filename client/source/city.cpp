#include "../headers/city.h"
#include <QJsonObject>
#include <QJsonArray>

City::City(const QString& name, const double& x, const double& y) : Point(x, y), name(name) {}

QJsonObject City::toJson() const {
    QJsonObject obj = Point::toJson();
    obj["name"] = name;
    return obj;
}
