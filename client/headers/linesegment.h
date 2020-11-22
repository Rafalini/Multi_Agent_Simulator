#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <memory>
#include <QVector>
#include <QObject>
#include "point.h"

QT_FORWARD_DECLARE_CLASS(Point); //forward declaration


class LineSegment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Point* begining MEMBER begining);
    Q_PROPERTY(Point* end MEMBER end);
    Q_PROPERTY(double length MEMBER length );

public:
    LineSegment(int id, Point* beg, Point* en, double len);
    QJsonObject toJson() const;
    int getId() const;
    ~LineSegment();

private:
    int id;
    Point* begining;
    Point* end;
    double length;
};

#endif // LINESEGMENT_H
