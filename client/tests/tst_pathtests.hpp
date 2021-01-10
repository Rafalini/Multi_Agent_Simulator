#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/path.h"

// add necessary includes here

class PathTests : public QObject
{
    Q_OBJECT

public:
    PathTests()
    {}

    ~PathTests()
    {}

private slots:
    void jsonTests()
    {
        Point point1(0.17, 0.18);
        Point point2(0.1243, 0.123);
        Path path(&point1, &point2, Path::HIGHWAY);
        QJsonObject comparableJson;
        comparableJson["id"] = path.getId();
        comparableJson["begining"] = point1.getId();
        comparableJson["end"] = point2.getId();
        comparableJson["type"] = Path::HIGHWAY;
        QCOMPARE(comparableJson, path.toJson());
        comparableJson["type"] = Path::DUALCARRIAGEWAY;
        path.setType(Path::DUALCARRIAGEWAY);
        QCOMPARE(comparableJson, path.toJson());
    }

};

