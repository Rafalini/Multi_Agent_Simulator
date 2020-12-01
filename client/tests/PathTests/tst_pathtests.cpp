#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/path.h"

// add necessary includes here

class PathTests : public QObject
{
    Q_OBJECT

public:
    PathTests();
    ~PathTests();

private slots:
    void test_case1();

};

PathTests::PathTests()
{

}

PathTests::~PathTests()
{

}

void PathTests::test_case1()
{

}

QTEST_APPLESS_MAIN(PathTests)

#include "tst_pathtests.moc"
