#ifndef TST_TESTBODY_H
#define TST_TESTBODY_H

#include <QObject>
#include <QtTest>

class TestBody : public QObject
{
    Q_OBJECT
public:
    explicit TestBody(QObject *parent = 0);

private Q_SLOTS:
    //void testId();
    void testPosition();
    void testVelocity();
    void testAcceleration();
    void testMass();
//    void testDiameter();
    void testMoveable();
//    void testName();
//    void testRotation();
//    void testTick();
    void testAffectedByGravity();
    void testForces();
    void TestRead();
    void TestWrite();

};

#endif // TST_TESTBODY_H
