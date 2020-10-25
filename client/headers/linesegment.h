#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <memory>
#include <QObject>
#include "point.h"
class Point; //forward declaration

class LineSegment : public QObject
{
    Q_OBJECT
public:
    LineSegment(int id, std::shared_ptr<Point> beg, std::shared_ptr<Point> en, double len);
    QJsonObject toJson();
    int getId() const;

private:
    int id;
    std::shared_ptr<Point> begining;
    std::shared_ptr<Point> end;
    double length;
};

#endif // LINESEGMENT_H
