#include "tst_testrenderbody.h"

TestRenderBody::TestRenderBody(QObject *parent) :
    QObject(parent)
{
}

void TestRenderBody::testRead()
{
    RenderBody b;

    //b.loadImageByteArray("a");
    b.createGraphic();

    QJsonObject json;
    b.read(json);

    qDebug() << json["sprite"];
    //qDebug() << b.getSprite();
    QVERIFY(false);
}

void TestRenderBody::testWrite()
{
    QVERIFY(false);
}
