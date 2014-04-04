#ifndef CLIENTGRAPHICSVIEW_H
#define CLIENTGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class ClientGraphicsView : public QGraphicsView
{
public:
    explicit ClientGraphicsView(QObject *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // CLIENTGRAPHICSVIEW_H
