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
//BASIC MAP
//    addCity("Kraków", 0.55, 0.85);
//    addCity("Warszawa", 0.65, 0.4);
//    addCity("Szczecin", 0.1, 0.12);
//    addPoint(0.1, 0.5);
//    addPoint(0.5, 0.7);
//    addPath(getCities()[0], getPoints()[0]);
//    addPath(getCities()[0], getPoints()[1]);
//    addPath(getCities()[1], getPoints()[0]);
//    addPath(getCities()[1], getPoints()[1]);
//    addPath(getCities()[2], getPoints()[0]);
//    addPath(getCities()[2], getCities()[1]);


//FULL MAP
    addCity("Kraków", 0.5731213872832371, 0.85);  //0 - 0
    addCity("Warszawa", 0.6719653179190753, 0.39884393063583834); //1 - 1
    addCity("Szczecin", 0.1, 0.12); //2 - 2
    addCity("Białystok", 0.8455284552845529, 0.2764227642276423); // 3 - 5
    addCity("Gdańsk", 0.4476761125992762, 0.11035293011889657); // 4 - 6
    addCity("Bydgoszcz", 0.4288617886178863, 0.22357723577235777); // 5 - 7
    addCity("Poznań", 0.26016260162601634, 0.3556910569105693);// 6 - 8
    addCity("Wrocław", 0.22201231260867552, 0.6401687109356643); // 7 - 9
    addCity("Zielona Góra", 0.10772357723577239, 0.4268292682926829); // 8 - 10
    addCity("Gorzów Wielkopolski", 0.12398373983739838, 0.2621951219512197); // 9 - 11
    addCity("Rzeszów", 0.7624277456647398, 0.8653179190751445); // 10 - 12
    addCity("Katowice", 0.4815028901734106, 0.769364161849711); // 11 - 13
    addCity("Łódź", 0.5219653179190756, 0.44450867052023163); // 12 - 14
    addCity("Lublin", 0.8213872832369947, 0.6514450867052026); //13 - 15
    addCity("Opole", 0.38786127167630075, 0.6919075144508671); //14 - 16
    addCity("Kielce", 0.6364161849710982, 0.6225433526011561); //15 - 17
    addCity("Olsztyn", 0.6271676300578036, 0.17283236994219653); //16 - 21
    addPoint(0.25028901734104053, 0.09884393063583821); //0 - 18 (środek między gdańskiem a szczecinem)
    addPoint(0.26878612716763006, 0.20751445086705206); //1 - 19 (środek między gorzowem a bydgoszczą)
    addPoint(0.7947976878612719, 0.18901734104046244); //2 - 20 (Punkt na prawo od Olsztyna)
    addPoint(0.8456647398843933, 0.4364161849710984); //3 - 22 (Punkt między Białymstokiem, a Lublinem)
    addPoint(0.7070595478406392, 0.545292876125849); //4 - 24 (Punkt między Warszawą a Kielcami)
    addPoint(0.13005780346820808, 0.35317919075144505); //5 - 25 (Punkt na lewo od Poznania)
    addPoint(0.6520605450074927, 0.3308768804446); //6 - 26 (Punkt między Warszawą, a Olsztynem)
    addPoint(0.5068613642481179, 0.2909729084569247); //7 - 27

    addPath(cities[4], cities[5]); // Gdańsk - Bydgoszcz
    addPath(cities[1], cities[12], Path::HIGHWAY); // Warszawa - Łódź
    addPath(cities[12], cities[6], Path::HIGHWAY); // Łódź - Poznań
    addPath(cities[9], cities[2], Path::DUALCARRIAGEWAY); // Gorzów Wielkopolski - Szczecin
    addPath(cities[6], points[1]); // Poznań - punkt 1
    addPath(cities[4], points[0]); // Gdańsk - punkt 0
    addPath(points[0], cities[2]); // punkt 0 - Szczenin
    addPath(points[0], points[1]); // punkt 0 - punkt 1
    addPath(points[0], points[1]); // punkt 0 - punkt 1
    addPath(points[1], cities[5]); // punkt 1 - Bydgoszcz
    addPath(points[1], cities[2]); // punkt 1 - Szczecin
    addPath(cities[16], points[2]); // Olsztyn - Punkt 2
    addPath(points[2], cities[3]); // Punkt 2 - Białystok
    addPath(cities[16], cities[4]); // Olsztyn - Gdańsk
    addPath(cities[3], cities[1]); // Białystok - Warszawa
    addPath(cities[3], points[3]); // Białystok - Punkt 3
    addPath(points[3], cities[13]); // Punkt 3 - Lublin
    addPath(points[3], cities[1]); // Punkt 3 - Warszawa
    addPath(cities[13], cities[10]); // Lublin - Rzeszów
    addPath(cities[12], cities[11]); // Łódź - Katowice
    addPath(cities[1], points[4]); // Warszawa - Punkt 4
    addPath(points[4], cities[15]); // Punkt 4 - Kielce
    addPath(points[4], cities[10]); // Punkt 4 - Rzeszów
    addPath(cities[15], cities[0]); // Kielce - Kraków
    addPath(cities[0], cities[11]); // Kraków - Katowice
    addPath(cities[0], cities[10]); // Kraków - Rzeszów
    addPath(cities[11], cities[14]); // Katowice - Opole
    addPath(cities[14], cities[7]); // Opole - Wrocław
    addPath(cities[7], cities[6]); // Wrocław - Poznań
    addPath(cities[7], cities[8]); // Wrocław - Zielona Góra
    addPath(points[5], cities[6]); // Punkt 5 - Poznań
    addPath(points[5], cities[9]); // Punkt 5 - Gorzów Wielkopolski
    addPath(points[5], cities[8]); // Punkt 5 - Zielona Góra
    addPath(cities[16], points[6]); // Olsztyn - Punkt 6
    addPath(points[6], cities[1]); // Punkt 6 - Warszawa
    addPath(points[6], points[7]); // Punkt 6 - Punkt 7
    addPath(points[7], cities[5]); // Punkt 6 - Bydgoszcz
    addPath(points[7], cities[12]); // Punkt 6 - Łódź
    addPath(cities[6], points[1]); // Poznań - Punkt 1
}


void MapProperties::addCity(const QString& name, const double& x, const double& y) {
    for(auto* city : cities) {
        if(city->getName() == name) {
            emit duplicateCityName(name);
            return;
        }
    }
    City* city = new City(name, x, y, nextPointId++);
    cities.push_back(city);
    emit citiesChanged();
}

void MapProperties::addPoint(const double& x, const double& y) {
    Point* point = new Point(x, y, nextPointId++);
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

    Point* point = new Point(x, y, nextPointId++);
    Path* firstPath = new Path(nextPathId++, begining, point, type);
    Path* secondPath = new Path(nextPathId++, point, end, type);
    point->addPath(firstPath);
    point->addPath(secondPath);
    paths.push_back(firstPath);
    paths.push_back(secondPath);
    points.push_back(point);
    emit pathsChanged();
    emit pointsChanged();
}


City* MapProperties::getCityById(int id) {
    for(auto city : cities) {
        if(city->getId() == id)
            return city;
    }
    return nullptr;
}
Point* MapProperties::getPointById(int id) {
    for(auto point : points) {
        if(point->getId() == id)
            return point;
    }
    return nullptr;
}

void MapProperties::promotePointToCity(Point* point, QString name) {
    City* city = new City(name, point->getX(), point->getY(), point->getId());
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

void MapProperties::addPath(Point* begining, Point* end, Path::RoadType type) {
    if(begining == end) {
        emit pathEndOnBegining();
        return;
    }
    Path* path = new Path(nextPathId++, begining, end, type);
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
