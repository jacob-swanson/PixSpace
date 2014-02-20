#include "helper.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>
#include <vector>
#include <QColor>
#include <RenderBody>
#include <SimpleDataManager>

Helper::Helper()
{
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    background = QBrush(QColor(Qt::black));

    this->body.loadImageByteArray("a");
    this->body.createGraphic();
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->save();
    // Draw stuff
    painter->fillRect(event->rect(), background);

    // Center on ship
    QTransform transform;
    //transform.translate(cx, cy);
    //painter->setWorldTransform(transform);

    // Draw ship
    //painter->translate(shipx - this->ship.width()/2, shipy - this->ship.height()/2);
    painter->drawPixmap(200 - this->body.getGraphicsItem().width()/2, 200 - this->body.getGraphicsItem().height()/2, this->body.getGraphicsItem());

    painter->restore();
}
