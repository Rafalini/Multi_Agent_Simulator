#include "../headers/mapproperties.h"
#include "../headers/point.h"
#include "../headers/city.h"
#include "../headers/linesegment.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MapProperties::MapProperties() { }

QJsonDocument MapProperties::toJson() {
    QJsonDocument doc;

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

    doc.setObject(obj);
    return doc;
}

void MapProperties::addCity(QString name, int x, int y) {
    std::shared_ptr<City> city(new City(name, x, y));
    cities.push_back(city);
}

void MapProperties::addPoint(int x, int y) {
    std::shared_ptr<Point> point(new Point(x, y));
    points.push_back(point);
}

void MapProperties::addSegment(int length, std::shared_ptr<Point> begining, std::shared_ptr<Point> end) {
    std::shared_ptr<LineSegment> segment(new LineSegment(nextSegmentId++, begining, end, length));
    begining->addSegment(segment);
    end->addSegment(segment);
    segments.push_back(segment);
}

QVector<std::shared_ptr<City> > MapProperties::getCities() const
{
    return cities;
}

QVector<std::shared_ptr<Point> > MapProperties::getPoints() const
{
    return points;
}

QVector<std::shared_ptr<LineSegment> > MapProperties::getSegments() const
{
    return segments;
}
