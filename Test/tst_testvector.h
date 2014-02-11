#ifndef TST_TESTVECTOR_H
#define TST_TESTVECTOR_H
#include <QString>
#include <QtTest>

class TestVector : public QObject
{
    Q_OBJECT

public:
    TestVector();

private Q_SLOTS:
    void testVectorLength();
    void testVectorLength2();
    void testNormalized();
    void testNormalized2();
    void TestAdd();
    void TestSub();
    void TestMultiply();
    void TestDivide();
    void TestCompoundAdd();
    void TestCompoundSub();
    void TestCompoundMultiply();
    void TestCompoundDivide();
    void TestEquals();
    void TestNotEquals();};



#endif // TST_TESTVECTOR_H
