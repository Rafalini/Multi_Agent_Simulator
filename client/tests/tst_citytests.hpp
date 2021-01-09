#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/city.h"
#include "../../headers/path.h"

// add necessary includes here

class CityTests : public QObject
{
    Q_OBJECT

public:
    CityTests()
    {

    }

    ~CityTests()
    {

    }

private slots:
    void jsonTests() {
        double x = 0.1;
        double y = 0.17;
        QString name = "city_test";
        City city(name, x, y);
        QJsonObject comparableJson;
        comparableJson["x"] = x;
        comparableJson["y"] = y;
        comparableJson["name"] = name;
        comparableJson["id"] = city.getId();
        QCOMPARE(comparableJson, city.toJson());
    }
};

