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

void TestBody::TestRead()
{
    Vector position(1.0, 1.0);
    Vector velocity(2.0, 2.0);
    Vector acceleration(3.0, 3.0);

    QJsonObject positionObject;
    position.write(positionObject);

    QJsonObject velocityObject;
    velocity.write(velocityObject);

    QJsonObject accelerationObject;
    acceleration.write(accelerationObject);

    QJsonObject bodyObject;

    bodyObject["position"] = positionObject;
    bodyObject["velocity"] = velocityObject;
    bodyObject["acceleration"] = accelerationObject;

    bodyObject["gravity"] = true;
    bodyObject["mass"] = 4.0;
    bodyObject["moveable"] = false;
    bodyObject["diameter"] = 5.0;
    bodyObject["rotation"] = 6.0;

    Body b;
    b.read(bodyObject);

    QCOMPARE(b.getPosition(), position);
    QCOMPARE(b.getVelocity(), velocity);
    QCOMPARE(b.getAcceleration(), acceleration);

    QCOMPARE(b.isAffectedByGravity(), true);
    QCOMPARE(b.getMass(), 4.0);
    QCOMPARE(b.isMoveable(), false);
    QCOMPARE(b.getDiameter(), 5.0);
    QCOMPARE(b.getRotation(), 6.0);
}

void TestBody::TestWrite()
{
    Vector position(1.0, 1.0);
    Vector velocity(2.0, 2.0);
    Vector acceleration(3.0, 3.0);

    Body b;
    b.setPosition(position);
    b.setVelocity(velocity);
    b.setAcceleration(acceleration);
    b.setAffectedByGravity(true);
    b.setMass(4.0);
    b.setMoveable(false);
    b.setDiameter(5.0);
    b.setRotation(6.0);

    QJsonObject bodyObject;
    b.write(bodyObject);

    Vector gotPosition;
    gotPosition.read(bodyObject["position"].toObject());
    QCOMPARE(gotPosition, position);

    Vector gotVelocity;
    gotVelocity.read(bodyObject["velocity"].toObject());
    QCOMPARE(gotVelocity, velocity);

    Vector gotAcceleration;
    gotAcceleration.read(bodyObject["acceleration"].toObject());
    QCOMPARE(gotAcceleration, acceleration);

    QCOMPARE(bodyObject["gravity"].toBool(), true);
    QCOMPARE(bodyObject["mass"].toDouble(), 4.0);
    QCOMPARE(bodyObject["moveable"].toBool(), false);
    QCOMPARE(bodyObject["diameter"].toDouble(), 5.0);
    QCOMPARE(bodyObject["rotation"].toDouble(), 6.0);

}
