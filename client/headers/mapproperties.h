#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QObject>
#include "city.h"
#include "linesegment.h"
#include "point.h"

class MapProperties : public QObject
{
    Q_OBJECT
public:
    MapProperties();
    QJsonDocument toJson();
    Q_INVOKABLE QVector<std::shared_ptr<LineSegment>> getSegments() const;
    Q_INVOKABLE QVector<std::shared_ptr<Point> > getPoints() const;
    Q_INVOKABLE QVector<std::shared_ptr<City> > getCities() const;
    Q_INVOKABLE void addCity(QString name, int x, int y);
    Q_INVOKABLE void addPoint(int x, int y);
    Q_INVOKABLE void addSegment(int length, std::shared_ptr<Point> begining, std::shared_ptr<Point> end);


private:
    QVector<std::shared_ptr<City>> cities;
    QVector<std::shared_ptr<Point>> points;
    QVector<std::shared_ptr<LineSegment>> segments;
    int nextSegmentId = 0;
};

#endif // MAPPROPERTIES_H
