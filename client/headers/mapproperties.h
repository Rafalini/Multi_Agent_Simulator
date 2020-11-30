#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QObject>
#include "city.h"
#include "path.h"
#include "point.h"

class MapProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<Path*> paths READ getPaths);
    Q_PROPERTY(QVector<City*> cities READ getCities);
    Q_PROPERTY(QVector<Point*> points READ getPoints);

public:
    MapProperties();
    QJsonObject toJson() const;
    virtual ~MapProperties();
    QVector<Path*> getPaths() const;
    QVector<Point*> getPoints() const;
    QVector<City*> getCities() const;
    Q_INVOKABLE void addCity(const QString& name, const double& x, const double& y);
    Q_INVOKABLE void addPoint(const double& x, const double& y);
    Q_INVOKABLE void addPath(const double& length, Point* begining, Point* end);
    Q_INVOKABLE void removePoint(Point* point);
    Q_INVOKABLE void removeCity(City* city);
    Q_INVOKABLE void removePath(Path* path);

signals:
    void cityAdded(City*);
    void duplicateCityName(QString);
    void pointAdded(Point*);
    void pathAdded(Path*);

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<Path*> paths;
    int nextPathId = 0;
};

#endif // MAPPROPERTIES_H
