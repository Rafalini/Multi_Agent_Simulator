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
    virtual ~MapProperties();
    QVector<LineSegment*> getSegments() const;
    QVector<Point*> getPoints() const;
    QVector<City*> getCities() const;
    Q_INVOKABLE void addCity(const QString& name, const double& x, const double& y);
    Q_INVOKABLE void addPoint(const double& x, const double& y);
    Q_INVOKABLE void addSegment(const double& length, Point* begining, Point* end);

signals:
    void cityAdded(City*);
    void duplicateCityName(QString);
    void pointAdded(Point*);
    void segmentAdded(LineSegment*);

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<LineSegment*> segments;
    int nextSegmentId = 0;
};

#endif // MAPPROPERTIES_H
