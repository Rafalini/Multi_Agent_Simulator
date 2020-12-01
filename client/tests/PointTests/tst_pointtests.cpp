#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/path.h"

class PointTests : public QObject
{
    Q_OBJECT

public:
    PointTests();
    ~PointTests();

private slots:
    void pointTests();
    void jsonTests();
    void negativeValueTests();
    void bigNumberTests();
};

PointTests::PointTests() {
}

void PointTests::negativeValueTests() {
    double x = 0.2;
    double y = 0.6;
    //NEGATIVE VALUES TEST
    double negative = -0.1;
    double negative2 = -0.4;
    //NEGATIVE X
    Point point2(negative, y);
    QVERIFY(point2.getX() != negative);
    QCOMPARE(point2.getX(), 0);
    QCOMPARE(point2.getY(), y);
    //NEGATIVE Y
    Point point3(x, negative2);
    QVERIFY(point3.getY() != negative2);
    QCOMPARE(point3.getX(), x);
    QCOMPARE(point3.getY(), 0);
    //BOTH NEGATIVE
    Point point4(negative, negative2);
    QVERIFY(point4.getX() != negative);
    QVERIFY(point4.getY() != negative2);
    QCOMPARE(point4.getX(), 0);
    QCOMPARE(point4.getY(), 0);
}

void PointTests::pointTests() {
    double x = 0.1;
    double y = 0.17;
    //CORRECT VALUES
    Point point(x, y);
    QCOMPARE(point.getX(), x);
    QCOMPARE(point.getY(), y);
}

void PointTests::bigNumberTests() {
    double x = 0.1;
    double y = 0.17;
    double bigNumber = 1.1;
    double bigNumber2 = 20.3;
    //BIG X
    Point point2(bigNumber, y);
    QVERIFY(point2.getX() != bigNumber);
    QCOMPARE(point2.getX(), 1);
    QCOMPARE(point2.getY(), y);
    //BIG Y
    Point point3(x, bigNumber2);
    QVERIFY(point3.getY() != bigNumber2);
    QCOMPARE(point3.getX(), x);
    QCOMPARE(point3.getY(), 1);
    //BOTH BIG
    Point point4(bigNumber, bigNumber2);
    QVERIFY(point4.getX() != bigNumber);
    QVERIFY(point4.getY() != bigNumber2);
    QCOMPARE(point4.getX(), 1);
    QCOMPARE(point4.getY(), 1);

}

void PointTests::jsonTests() {
    double x = 0.1;
    double y = 0.17;
    Point point(x, y);

    QVector<Path*> paths;

    QJsonObject comparableJson;
    comparableJson["x"] = x;
    comparableJson["y"] = y;
    QJsonArray path;
    for(auto *obj : paths) {
         path.append(obj->toJson());
         point.addPath(obj);
    }
    comparableJson["paths"] = path;
    QCOMPARE(comparableJson, point.toJson());
    //next test should check when list of segments is not null
}

PointTests::~PointTests()
{

}

QTEST_APPLESS_MAIN(PointTests)

#include "tst_pointtests.moc"
