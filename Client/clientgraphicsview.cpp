#include "clientgraphicsview.h"

ClientGraphicsView::ClientGraphicsView(QObject *parent) :
    QGraphicsView()
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    this->controller = NULL;
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

void ClientGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    // Draw the HUD
    if (this->controller != NULL && this->controller->getPossessed() != NULL)
    {
        // Setup the painter
        QPainter painter(this->viewport());
        painter.setPen(QColor(Qt::white));

        QFont f;
        f.setPointSize(24);
        f.setCapitalization(QFont::SmallCaps);
        painter.setFont(f);

        painter.drawText(50, 50, "Velocity: " + QString::number(this->controller->getPossessed()->getVelocity().length()) +  " m/s");
        painter.drawText(50, 100, "Throttle: " + QString::number(this->controller->getPossessed()->getThrottle() * 100) +  " %");

        // End the painter
        painter.end();
        this->viewport()->update();
    }
}

void ClientGraphicsView::setController(PlayerController *controller)
{
    this->controller = controller;
}
