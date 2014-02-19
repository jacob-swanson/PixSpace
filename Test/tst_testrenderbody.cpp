#include "tst_testrenderbody.h"
#include <SimpleDataManager>
#include <QDebug>
#include <QString>

TestRenderBody::TestRenderBody(QObject *parent) :
    QObject(parent)
{
}

void TestRenderBody::testGetSprite()
{
    SimpleDataManager s;
    QString sprite;
    s.loadBodySprite(QString("ship1"), &sprite);
    qDebug() << sprite;
}
