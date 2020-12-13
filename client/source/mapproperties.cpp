#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "mapproperties.h"
#include "point.h"
#include "city.h"
#include "path.h"

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

void MapProperties::fill() {
    if(cities.size() > 0) return;

    addCity("Kraków", 0.55, 0.85);
    addCity("Warszawa", 0.65, 0.4);
    addCity("Szczecin", 0.1, 0.12);
    addPoint(0.1, 0.5);
    addPoint(0.5, 0.7);
    addPath(getCities()[0], getPoints()[0]);
    addPath(getCities()[0], getPoints()[1]);
    addPath(getCities()[1], getPoints()[0]);
    addPath(getCities()[1], getPoints()[1]);
    addPath(getCities()[2], getPoints()[0]);
    addPath(getCities()[2], getCities()[1]);
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
    emit citiesChanged();
}

void MapProperties::addPoint(const double& x, const double& y) {
    Point* point = new Point(x, y);
    points.push_back(point);
    emit pointsChanged();
}

void MapProperties::splitPath(Path * old_path, double x, double y) {
    paths.removeOne(old_path);
    Point* begining = old_path->getBegining();
    begining->removePath(old_path);
    Point* end = old_path->getEnd();
    end->removePath(old_path);
    delete old_path;

    Point* point = new Point(x, y);
    Path* firstPath = new Path(nextPathId++, begining, point);
    Path* secondPath = new Path(nextPathId++, point, end);
    paths.push_back(firstPath);
    paths.push_back(secondPath);
    points.push_back(point);
    emit pathsChanged();
    emit pointsChanged();
}

void MapProperties::promotePointToCity(Point* point, QString name) {
    City* city = new City(name, point->getX(), point->getY());
    cities.push_back(city);
    points.removeOne(point);
    for(auto path : point->getPaths()) {
        if(path->getBegining() == point) {
            path->setBegining(city);
        }
        if(path->getEnd() == point) {
            path->setEnd(city);
        }
    }
    emit pointsChanged();
    emit citiesChanged();
    delete point;
}

void MapProperties::addPath(Point* begining, Point* end) {
    if(begining == end) {
        emit pathEndOnBegining();
        return;
    }
    Path* path = new Path(nextPathId++, begining, end);
    for(auto old_path : paths) {
        if(*path == *old_path) {
            emit pathAlreadyExist();
            delete path;
            return;
        }
    }
    begining->addPath(path);
    end->addPath(path);
    paths.push_back(path);
    emit pathsChanged();
}

MapProperties::~MapProperties() {
    while(!cities.isEmpty()) {
       City* city = cities.takeLast();
       emit citiesChanged();
       delete city;
    }
    while(!points.isEmpty()) {
       Point* point = points.takeLast();
       emit pointsChanged();
       delete point;
    }
    while(!paths.isEmpty()) {
       Path* path = paths.takeLast();
       emit pathsChanged();
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
    for(auto path : point->getPaths()) {
        removePath(path);
    }
    points.removeOne(point);
    emit pointsChanged();
    delete point;
}

void MapProperties::removeCity(City* city) {
    if( city == nullptr ) return;
    for(auto path : city->getPaths()) {
        removePath(path);
    }
    cities.removeOne(city);
    emit citiesChanged();
    delete city;
}

void MapProperties::removePath(Path* path) {
    if( path == nullptr ) return;
    paths.removeOne(path);
    emit pathsChanged();
    delete path;
}
