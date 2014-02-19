#include <QtTest>
#include <QTimer>
#include "tst_testvector.h"
#include "tst_testbody.h"
#include "tst_testrenderbody.h"

int main(int argc, char *argv[])
{
    TestVector testVector;
    int ret = QTest::qExec(&testVector, argc, argv);

    TestBody testBody;
    ret += QTest::qExec(&testBody, argc, argv);

    return ret;
}
