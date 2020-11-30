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
        emit removed(this);
        end->removePath(this);
    } else if(end == point) {
        emit aboutToDelete();
        end = nullptr;
        emit removed(this);
        begining->removePath(this);
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
