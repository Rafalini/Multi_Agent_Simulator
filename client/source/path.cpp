#include <QJsonObject>
#include <QJsonArray>
#include "path.h"

Path::Path(int id, Point* beg, Point* en) : id(id), begining(beg), end(en) {}

int Path::getId() const
{
    return id;
}

Path::~Path() {
    if(begining != nullptr)
        begining->removePath(this);
    if(end != nullptr )
        end->removePath(this);
}

Point* Path::getBegining() const
{
    return begining;
}

Point* Path::getEnd() const
{
    return end;
}


bool Path::operator==(const Path& o) const {
    return (this->begining == o.begining && this->end == o.end) || (this->end == o.begining && this->begining == o.end);
}

void Path::setBegining(Point* begining) {
    if(begining == nullptr) return;
    this->begining = begining;
    this->begining->addPath(this);
    emit beginingChanged();
}

void Path::setEnd(Point* end) {
    if(end == nullptr) return;
    this->end->removePath(this);
    this->end = end;
    this->end->addPath(this);
    emit endChanged();
}


QJsonObject Path::toJson() const {
    QJsonObject obj;
    obj["id"] = id;
    obj["x1"] = begining->getX();
    obj["y1"] = begining->getY();
    obj["x2"] = end->getX();
    obj["y2"] = end->getY();
    return obj;
}
