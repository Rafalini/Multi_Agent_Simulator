#ifndef PATH_H
#define PATH_H

#include <memory>
#include <QVector>
#include <QObject>
#include <QJsonObject>
#include "Point.h"

QT_FORWARD_DECLARE_CLASS(Point); //forward declaration


class Path : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Point* begining READ getBegining WRITE setBegining NOTIFY beginingChanged);
    Q_PROPERTY(Point* end READ getEnd WRITE setEnd NOTIFY endChanged);
    Q_PROPERTY(RoadType type READ getType WRITE setType NOTIFY typeChanged);
    Q_PROPERTY(QJsonObject trafficData READ getTrafficData NOTIFY trafficDataChanged);

public:
    enum RoadType {
        STANDARD = 0,
        DUALCARRIAGEWAY,
        HIGHWAY
    };
    Q_ENUMS(RoadType)

    Path(Point* beg, Point* en, RoadType type);
    Path(Point* beg, Point* en, RoadType type, const int& id);
    QJsonObject toJson() const;
    int getId() const;
    virtual ~Path();
    void setBegining(Point*);
    void setEnd(Point*);
    Point* getBegining() const;
    Point* getEnd() const;
    bool operator==(const Path&) const;
    RoadType getType() const;
    void setType(const RoadType &value);
    QJsonObject getTrafficData() const;
    void setTrafficData(const QJsonObject &value);

signals:
    void endChanged();
    void beginingChanged();
    void typeChanged();
    void trafficDataChanged();

private:
    int id;
    Point* begining;
    Point* end;
    RoadType type;
    QJsonObject trafficData;
    static int next_id;
};

#endif // PATH_H
