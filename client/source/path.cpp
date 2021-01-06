#include <QJsonObject>
#include <QJsonArray>
#include "path.h"

Path::Path(int id, Point* beg, Point* en, RoadType type) : id(id), begining(beg), end(en), type(type) {}

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

Path::RoadType Path::getType() const
{
    return type;
}

void Path::setType(const RoadType &value)
{
    type = value;
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
    obj["begining"] = begining->getId();
    obj["end"] = end->getId();
    obj["type"] = 0;
    return obj;
}
