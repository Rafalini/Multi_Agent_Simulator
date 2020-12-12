#ifndef PATH_H
#define PATH_H

#include <memory>
#include <QVector>
#include <QObject>
#include "point.h"

QT_FORWARD_DECLARE_CLASS(Point); //forward declaration


class Path : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Point* begining READ getBegining WRITE setBegining NOTIFY beginingChanged);
    Q_PROPERTY(Point* end READ getEnd WRITE setEnd NOTIFY endChanged);

public:
    Path(int id, Point* beg, Point* en);
    QJsonObject toJson() const;
    int getId() const;
    virtual ~Path();
    void setBegining(Point*);
    void setEnd(Point*);
    Point* getBegining() const;
    Point* getEnd() const;
    bool operator==(const Path&) const;

signals:
    void endChanged();
    void beginingChanged();

private:
    int id;
    Point* begining;
    Point* end;
};

#endif // PATH_H
