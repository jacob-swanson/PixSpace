#include <QDebug>
#include "tst_testvector.h"
#include <Vector>

TestVector::TestVector()
{
}

void TestVector::testVectorLength()
{
    Vector v(0,0);

    double got = v.length();
    double expected = 0;

    QVERIFY(got == expected);
}

void TestVector::testVectorLength2()
{
    Vector v(1,1);

    double got = v.length();
    double min = 1.40;
    double max = 1.42;

    QVERIFY((got > min) && (got < max));
}

void TestVector::testNormalized()
{
    Vector v(0,0);

    Vector norm = v.normalized();
    Vector expected(0,0);

    QVERIFY(norm == expected);
}

void TestVector::testNormalized2()
{
    Vector v(1,1);

    Vector norm = v.normalized();
    Vector min(0.69,0.69);
    Vector max(0.71,0.71);


    QVERIFY((norm.getX() > min.getX()) && (norm.getX() < max.getX()));
    QVERIFY((norm.getY() > min.getY()) && (norm.getY() < max.getY()));
}

void TestVector::TestAdd()
{
    Vector v(1,1);
    Vector v2(1,1);

    Vector v3 = v + v2;
    Vector expected(2,2);

    QVERIFY(v3 == expected);
}

void TestVector::TestSub()
{
    Vector v(1,1);
    Vector v2(1,1);

    Vector v3 = v - v2;
    Vector expected(0,0);

    QVERIFY(v3 == expected);
}

void TestVector::TestMultiply()
{
    Vector v(1,1);

    Vector v2 = v*2;
    Vector expected(2,2);

    QVERIFY(v2 == expected);
}

void TestVector::TestDivide()
{
    Vector v(4,4);

    Vector v2 = v/2;
    Vector expected(2,2);

    QVERIFY(v2 == expected);
}

void TestVector::TestCompoundAdd()
{
    Vector v(1,1);

    Vector v2(1,1);
    v2 += v;
    Vector expected(2,2);

    QVERIFY(v2 == expected);
}

void TestVector::TestCompoundSub()
{
    Vector v(1,1);

    Vector v2(1,1);
    v2 -= v;
    Vector expected(0,0);

    QVERIFY(v2 == expected);
}

void TestVector::TestCompoundMultiply()
{
    Vector v(2,2);

    v *= 4;
    Vector expected(8,8);

    QVERIFY(v == expected);
}

void TestVector::TestCompoundDivide()
{
    Vector v(4,4);

    v /= 2;
    Vector expected(2,2);

    QVERIFY(v == expected);
}

void TestVector::TestEquals()
{
    Vector v(1,1);
    Vector v2(1,1);

    QVERIFY(v == v2);
}

void TestVector::TestNotEquals()
{
    Vector v(1,1);
    Vector v2(2,2);

    QVERIFY(v != v2);
}
