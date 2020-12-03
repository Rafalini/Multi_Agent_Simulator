#include "../headers/path.h"
#include <QJsonObject>
#include <QJsonArray>

Path::Path(int id, Point* beg, Point* en, double len) : id(id), begining(beg), end(en), length(len) {}

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

void Path::setBegining(Point* begining) {
    if(begining == nullptr) return;
    this->end = begining;
    emit beginingChanged();
}

void Path::setEnd(Point* end) {
    if(end == nullptr) return;
    this->end = end;
    emit endChanged();
}


QJsonObject Path::toJson() const {
    QJsonObject obj;
    obj["id"] = id;
    obj["x1"] = begining->getX();
    obj["y1"] = begining->getY();
    obj["x2"] = end->getX();
    obj["y2"] = end->getY();
    obj["length"] = length;
    return obj;
}
