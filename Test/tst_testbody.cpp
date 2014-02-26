#include "tst_testbody.h"
#include <Body>
#include <Vector>
#include <QtTest>

TestBody::TestBody(QObject *parent) :
    QObject(parent)
{
}

void TestBody::testPosition()
{
    Body b;
    QCOMPARE(b.getPosition(), Vector(0.0,0.0));

    b.setPosition(0.0,1.0);
    QCOMPARE(b.getPosition(), Vector(0.0,1.0));

    b.setPosition(Vector(0.0,1.0));
    QCOMPARE(b.getPosition(), Vector(0.0,1.0));

    b.setPosition(0.0,0.0);
    b.updatePosition(Vector(1.0,1.0));
    QCOMPARE(b.getPosition(), Vector(1.0,1.0));
}

void TestBody::testVelocity()
{
    Body b;
    QCOMPARE(b.getVelocity(), Vector(0.0,0.0));

    b.setVelocity(0.0,1.0);
    QCOMPARE(b.getVelocity(), Vector(0.0,1.0));

    b.setVelocity(0.0,0.0);
    b.updateVelocity(Vector(1.0,1.0));
    QCOMPARE(b.getVelocity(), Vector(1.0,1.0));
}

void TestBody::testAcceleration()
{
    Body b;
    QCOMPARE(b.getAcceleration(), Vector(0.0,0.0));

    b.setAcceleration(Vector(0.0,1.0));
    QCOMPARE(b.getAcceleration(), Vector(0.0,1.0));
}

void TestBody::testMass()
{
    Body b;
    QCOMPARE(b.getMass(), 0.0);

    b.setMass(1.0);
    QCOMPARE(b.getMass(), 1.0);
}

void TestBody::testMoveable()
{
    Body b;
    QVERIFY(b.isMoveable());

    b.setMoveable(false);
    QVERIFY(!b.isMoveable());
}

void TestBody::testAffectedByGravity()
{
    Body b;
    QVERIFY(b.isAffectedByGravity());

    b.setAffectedByGravity(false);
    QVERIFY(!b.isAffectedByGravity());
}

void TestBody::testForces()
{
    Body b;
    QVERIFY(b.isForcesEmpty());

    b.pushForce(Vector(1.0,1.0));
    QVERIFY(!b.isForcesEmpty());
    QCOMPARE(b.popForce(), Vector(1.0,1.0));
    QVERIFY(b.isForcesEmpty());
}

void TestVector::TestRead()
{

}

void TestVector::TestWrite()
{

}
