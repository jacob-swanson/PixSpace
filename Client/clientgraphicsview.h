#ifndef CLIENTGRAPHICSVIEW_H
#define CLIENTGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#include "playercontroller.h"

class ClientGraphicsView : public QGraphicsView
{
public:
    explicit ClientGraphicsView(QObject *parent = 0);

    void setController(PlayerController* controller);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    PlayerController* controller;
};

#endif // CLIENTGRAPHICSVIEW_H
