#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QObject>
#include "city.h"
#include "linesegment.h"
#include "point.h"

class MapProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<LineSegment*> segments MEMBER segments);
    Q_PROPERTY(QVector<City*> cities MEMBER cities);
    Q_PROPERTY(QVector<Point*> points MEMBER points);

public:
    MapProperties();
    QJsonObject toJson() const;
    ~MapProperties();
    Q_INVOKABLE QVector<LineSegment*> getSegments() const;
    Q_INVOKABLE QVector<Point*> getPoints() const;
    Q_INVOKABLE QVector<City*> getCities() const;
    Q_INVOKABLE void addCity(QString name, int x, int y);
    Q_INVOKABLE void addPoint(int x, int y);
    Q_INVOKABLE void addSegment(int length, Point* begining, Point* end);

signals:

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<LineSegment*> segments;
    int nextSegmentId = 0;
};

#endif // MAPPROPERTIES_H
