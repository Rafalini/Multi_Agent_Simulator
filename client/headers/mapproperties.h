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
    Q_INVOKABLE void addPath(const double& length, Point* begining, Point* end);
    Q_INVOKABLE void removePoint(Point* point);
    Q_INVOKABLE void removeCity(City* city);
    Q_INVOKABLE void removePath(Path* path);

signals:
    void duplicateCityName(QString);
    void pathsChanged();
    void citiesChanged();
    void pointsChanged();

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<Path*> paths;
    int nextPathId = 0;
};

#endif // MAPPROPERTIES_H
