#ifndef TST_TESTRENDERBODY_H
#define TST_TESTRENDERBODY_H

#include <QObject>
#include <QJsonObject>
#include <QtTest>

#include <RenderBody>

class TestRenderBody : public QObject
{
    Q_OBJECT
public:
    explicit TestRenderBody(QObject *parent = 0);

private Q_SLOTS:
    void testRead();
    void testWrite();
};

#endif // TST_TESTRENDERBODY_H
