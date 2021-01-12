#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include "mapproperties.h"
#include "point.h"
#include "city.h"
#include "path.h"

MapProperties::MapProperties() {
    QJsonDocument doc =  QJsonDocument::fromJson(mapJson.toUtf8());
    fill(doc);
}

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

void MapProperties::saveMapToJson() {
    QJsonObject mapJson = toJson();
    QJsonDocument doc;
    doc.setObject(mapJson);
    QDateTime current_date = QDateTime::currentDateTime();
    QString date = current_date.toString("yyyy-MM-dd-hh-mm-ss");
    QString fileName = "map"+date+".json";
    qDebug() << fileName;
    QFileDialog::saveFileContent(doc.toJson(), fileName.toUtf8());
}

void MapProperties::readMapFromJsonFile() {
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (!fileName.isEmpty()) {
            QJsonDocument doc = QJsonDocument::fromJson(fileContent);
            if(doc.toJson() == "") {
                emit fileFormatException();
                return;
            }
            emit aboutToClear();
            clear();
            fill(doc);
        }
    };
    QFileDialog::getOpenFileContent("Pliki (*.txt *.json)",  fileContentReady);
}

void MapProperties::clear() {
    while(!paths.isEmpty()) {
       Path* path = paths.takeLast();
       emit pathsChanged();
       path->deleteLater();;
    }
    while(!cities.isEmpty()) {
       City* city = cities.takeLast();
       emit citiesChanged();
       city->deleteLater();
    }
    while(!points.isEmpty()) {
       Point* point = points.takeLast();
       emit pointsChanged();
       point->deleteLater();
    }
}

void MapProperties::fill(const QJsonDocument& doc) {
    if(cities.size() > 0) return;
    QJsonObject map = doc.object();
    QJsonArray cities_ = map["cities"].toArray();
    for(int i = 0; i < cities_.size(); ++i) {
        QJsonObject city = cities_[i].toObject();
        addCity(city["name"].toString(), city["x"].toDouble(), city["y"].toDouble(), city["id"].toInt());
    }
    QJsonArray points_ = map["points"].toArray();
    for(int i = 0; i < points_.size(); ++i) {
        QJsonObject point = points_[i].toObject();
        addPoint(point["x"].toDouble(), point["y"].toDouble(), point["id"].toInt());
    }
    QJsonArray paths_ = map["paths"].toArray();
    for(int i = 0; i < paths_.size(); ++i) {
        QJsonObject path = paths_[i].toObject();
        addPath(getPointById(path["begining"].toInt()), getPointById(path["end"].toInt()), Path::RoadType(path["type"].toInt()), path["id"].toInt());
    }
}

void MapProperties::addCity(const QString& name, const double& x, const double& y, int id) {
    for(auto* city : cities) {
        if(city->getName() == name) {
            emit duplicateCityName(name);
            return;
        }
    }
    City* city;
    if(id < 0)
        city = new City(name, x, y);
    else
        city = new City(name, x, y, id);
    cities.push_back(city);
    emit citiesChanged();
}

void MapProperties::addPoint(const double& x, const double& y, int id) {
    Point* point;
    if(id < 0)
        point = new Point(x, y);
    else
        point = new Point(x, y, id);
    points.push_back(point);
    emit pointsChanged();
}

void MapProperties::splitPath(Path * old_path, double x, double y) {
    paths.removeOne(old_path);
    emit pathsChanged();
    Point* begining = old_path->getBegining();
    begining->removePath(old_path);
    Point* end = old_path->getEnd();
    end->removePath(old_path);
    Path::RoadType type = old_path->getType();
    delete old_path;

    Point* point = new Point(x, y);
    Path* firstPath = new Path(begining, point, type);
    Path* secondPath = new Path(point, end, type);
    point->addPath(firstPath);
    point->addPath(secondPath);
    paths.push_back(firstPath);
    paths.push_back(secondPath);
    points.push_back(point);
    emit pathsChanged();
    emit pointsChanged();
}

Point* MapProperties::getPointById(int id) {
    auto point = std::find_if(points.begin(), points.end(),
                              [&id](const Point* point) { return point->getId() == id;});
    if(point == points.end()) {
        auto city = std::find_if(cities.begin(), cities.end(),
                                 [&id](const City* city) { return city->getId() == id;});
        if(city == cities.end())
            return nullptr;
        return *city;
    }
    return *point;
}

Path *MapProperties::getPathById(int id) {
    return *std::find_if(paths.begin(), paths.end(),
                              [&id](const Path* path) { return path->getId() == id;});
}

void MapProperties::promotePointToCity(Point* point, QString name) {
    City* city = new City(name, point->getX(), point->getY());
    cities.push_back(city);
    points.removeOne(point);
    for(auto &path : point->getPaths()) {
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

void MapProperties::addPath(Point* begining, Point* end, Path::RoadType type, int id) {
    if(begining == end) {
        emit pathEndOnBegining();
        return;
    }
    Path* path;
    if(id < 0)
        path = new Path(begining, end, type);
    else
        path = new Path(begining, end, type, id);
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
    while(!paths.isEmpty()) {
       Path* path = paths.takeLast();
       emit pathsChanged();
       delete path;
    }
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
}

QVector<City*> MapProperties::getCities() const {
    return cities;
}

QVector<Point*> MapProperties::getPoints() const {
    return points;
}

QVector<Path*> MapProperties::getPaths() const {
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
