#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/linesegment.h"

class PointTests : public QObject
{
    Q_OBJECT

public:
    PointTests();
    ~PointTests();

private slots:
    void test_case1();

};

PointTests::PointTests()
{

}

PointTests::~PointTests()
{

}

void PointTests::test_case1()
{

}

QTEST_APPLESS_MAIN(PointTests)

#include "tst_pointtests.moc"
