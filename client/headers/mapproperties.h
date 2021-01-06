#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QObject>
#include "city.h"
#include "path.h"
#include "point.h"

class MapProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<Path*> paths READ getPaths NOTIFY pathsChanged);
    Q_PROPERTY(QVector<City*> cities READ getCities NOTIFY citiesChanged);
    Q_PROPERTY(QVector<Point*> points READ getPoints NOTIFY pointsChanged);

public:
    MapProperties();
    QJsonObject toJson() const;
    virtual ~MapProperties();
    QVector<Path*> getPaths() const;
    QVector<Point*> getPoints() const;
    QVector<City*> getCities() const;
    Q_INVOKABLE void addCity(const QString& name, const double& x, const double& y);
    Q_INVOKABLE void addPoint(const double& x, const double& y);
    Q_INVOKABLE void addPath(Point* begining, Point* end, Path::RoadType type = Path::STANDARD);
    Q_INVOKABLE void removePoint(Point* point);
    Q_INVOKABLE void removeCity(City* city);
    Q_INVOKABLE void removePath(Path* path);
    Q_INVOKABLE void splitPath(Path* old_path, double x, double y);
    Q_INVOKABLE void promotePointToCity(Point*, QString name);
    Q_INVOKABLE City* getCityById(int id);
    Q_INVOKABLE Point* getPointById(int id);
    void fill();

signals:
    void duplicateCityName(QString);
    void pathsChanged();
    void citiesChanged();
    void pointsChanged();
    void pathAlreadyExist();
    void pathEndOnBegining();

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<Path*> paths;
    int nextPathId = 0;
    int nextPointId = 0;
};

#endif // MAPPROPERTIES_H
