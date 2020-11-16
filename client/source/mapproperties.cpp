#include "../headers/mapproperties.h"
#include "../headers/point.h"
#include "../headers/city.h"
#include "../headers/linesegment.h"
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

    QJsonArray segmentsArray;
    for(auto &segment : segments) {
        QJsonObject jsonCity = segment->toJson();
        segmentsArray.append(jsonCity);
    }
    obj["segments"] = segmentsArray;
    return obj;
}

void MapProperties::addCity(const QString& name, const double& x, const double& y) {
    City* city = new City(name, x, y);
    cities.push_back(city);
}

void MapProperties::addPoint(const double& x, const double& y) {
    Point* point = new Point(x, y);
    points.push_back(point);
}

void MapProperties::addSegment(const double& length, Point* begining, Point* end) {
    LineSegment* segment = new LineSegment(nextSegmentId++, begining, end, length);
    begining->addSegment(segment);
    end->addSegment(segment);
    segments.push_back(segment);
}

MapProperties::~MapProperties() {
    for(auto& city : cities) {
        delete city;
    }
    for(auto& point : points) {
        delete point;
    }
    for(auto& segment : segments) {
        delete segment;
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

QVector<LineSegment*> MapProperties::getSegments() const
{
    return segments;
}
