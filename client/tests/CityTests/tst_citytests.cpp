#include <QtTest>
#include "../../headers/point.h"
#include "../../headers/city.h"
#include "../../headers/path.h"

// add necessary includes here

class CityTests : public QObject
{
    Q_OBJECT

public:
    CityTests();
    ~CityTests();

private slots:
    void test_case1();

};

CityTests::CityTests()
{

}

CityTests::~CityTests()
{

}

void CityTests::test_case1()
{
}

QTEST_APPLESS_MAIN(CityTests)

#include "tst_citytests.moc"
