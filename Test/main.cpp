#include <QtTest>
#include "tst_testvector.h"
#include "tst_testbody.h"

int main(int argc, char *argv[])
{
    TestVector testVector;
    int ret = QTest::qExec(&testVector, argc, argv);

    TestBody testBody;
    ret += QTest::qExec(&testBody, argc, argv);

    return ret;
}
