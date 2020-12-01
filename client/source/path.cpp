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
    emit deleted();
}

void Path::removePoint(Point* point) {
    if(begining == point) {
        emit aboutToDelete();
        begining = nullptr;
        if(end != nullptr)
            end->removePath(this);
        emit removed(this);
    } else if(end == point) {
        emit aboutToDelete();
        if(begining != nullptr)
            begining->removePath(this);
        end = nullptr;
        emit removed(this);
    }
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
