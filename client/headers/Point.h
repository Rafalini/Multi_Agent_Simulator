#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <QVector>
#include "Path.h"

QT_FORWARD_DECLARE_CLASS(Path); //forward declaration
//Class representing a point on map, where roads can split or merge, the coordinates are within range (0,1)
class Point : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged FINAL);
    Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged FINAL);

public:
    Point(const double& x, const double& y);
    Point(const double& x, const double& y, const int& id);
    virtual ~Point() {emit deleted();}
    const double& getX() const;
    void removePath(Path* path);
    QVector<Path*> getPaths() const;
    virtual QJsonObject toJson() const;
    int getId() const;
    const double& getY() const;
    Q_INVOKABLE void setX(const double& x);
    Q_INVOKABLE void setY(const double& y);
    Q_INVOKABLE void addPath(Path* path);

signals:
    void xChanged(const double&);
    void yChanged(const double&);
    void deleted();

protected:
    QVector<Path*> paths;
    double x;
    double y;
    int id;
    static int next_id;
};

#endif // POINT_H
