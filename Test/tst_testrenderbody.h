#ifndef TST_TESTRENDERBODY_H
#define TST_TESTRENDERBODY_H

#include <QObject>

class TestRenderBody : public QObject
{
    Q_OBJECT
public:
    explicit TestRenderBody(QObject *parent = 0);

private Q_SLOTS:
    void testGetSprite();

};

#endif // TST_TESTRENDERBODY_H
