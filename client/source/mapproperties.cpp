#include "../headers/mapproperties.h"
#include "../headers/point.h"
#include "../headers/city.h"
#include "../headers/path.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MapProperties::MapProperties() { }

QJsonObject MapProperties::toJson() const {
    QJsonObject obj;
    QJsonArray citiesArray;
    for(auto &city : cities) {
        QJsonObject jsonCity = city->toJson();
        citiesArray.append(jsonCity);
    }
    obj["cities"] = citiesArray;

    QJsonArray pointsArray;
    for(auto &point : points) {
        QJsonObject jsonCity = point->toJson();
        pointsArray.append(jsonCity);
    }
    obj["points"] = pointsArray;

    QJsonArray pathsArray;
    for(auto &path : paths) {
        QJsonObject jsonCity = path->toJson();
        pathsArray.append(jsonCity);
    }
    obj["paths"] = pathsArray;
    return obj;
}

void MapProperties::addCity(const QString& name, const double& x, const double& y) {
    for(auto* city : cities) {
        if(city->getName() == name) {
            emit duplicateCityName(name);
            return;
        }
    }
    City* city = new City(name, x, y);
    cities.push_back(city);
    emit cityAdded(city);
}

void MapProperties::addPoint(const double& x, const double& y) {
    Point* point = new Point(x, y);
    points.push_back(point);
    emit pointAdded(point);
}

void MapProperties::addPath(const double& length, Point* begining, Point* end) {
    Path* path = new Path(nextPathId++, begining, end, length);
    begining->addPath(path);
    end->addPath(path);
    paths.push_back(path);
    connect(path, &Path::removed, [=](Path* path){delete path;});
}

MapProperties::~MapProperties() {
    for(auto& city : cities) {
        delete city;
    }
    for(auto& point : points) {
        delete point;
    }
    for(auto& path : paths) {
        delete path;
    }
}

QVector<City*> MapProperties::getCities() const
{
    return cities;
}

QVector<Point*> MapProperties::getPoints() const
{
    return points;
}

QVector<Path*> MapProperties::getPaths() const
{
    return paths;
}


void MapProperties::removePoint(Point* point) {
    if( point == nullptr ) return;
    points.removeOne(point);
    delete point;
}
void MapProperties::removeCity(City* city) {
    if( city == nullptr ) return;
    cities.removeOne(city);
    delete city;
}
void MapProperties::removePath(Path* path) {
    if( path == nullptr ) return;
    paths.removeOne(path);
    delete path;
}
