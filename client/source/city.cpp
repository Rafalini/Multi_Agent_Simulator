#include "../headers/city.h"
#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>

City::City(QString name, double x, double y) : Point(x, y), name(name) {}

QJsonObject City::toJson() const {
    QJsonObject obj = Point::toJson();
    obj["name"] = name;
    return obj;
}
