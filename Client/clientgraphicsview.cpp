#include "clientgraphicsview.h"

ClientGraphicsView::ClientGraphicsView(QObject *parent) :
    QGraphicsView()
{
}

void ClientGraphicsView::wheelEvent(QWheelEvent *event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double scaleFactor = 1.15;
    if (event->delta() > 0)
    {
        this->scale(scaleFactor, scaleFactor);
    }
    else
    {
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
