#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/linesegment.h"

// add necessary includes here

class LineSegmentTests : public QObject
{
    Q_OBJECT

public:
    LineSegmentTests();
    ~LineSegmentTests();

private slots:
    void test_case1();

};

LineSegmentTests::LineSegmentTests()
{

}

LineSegmentTests::~LineSegmentTests()
{

}

void LineSegmentTests::test_case1()
{

}

QTEST_APPLESS_MAIN(LineSegmentTests)

#include "tst_linesegmenttests.moc"
