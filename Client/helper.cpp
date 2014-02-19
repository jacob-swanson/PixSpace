#include "helper.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include "../Shared/SimpleDataManager"

Helper::Helper()
{
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    background = QBrush(QColor(Qt::black));

    QString sprite;
    SimpleDataManager dm;
    if (dm.loadBodySprite(QString("a"), &sprite))
    {
       // qDebug() << sprite;
    }
    else
    {
        qDebug() << "Could not load sprite";
    }

    QByteArray ba = sprite.toLocal8Bit();
    const char *ship_xpm = ba.data();
    this->ship = QPixmap(ship_xpm);
    qDebug() << ship;
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->save();
    // Draw stuff
    //painter->fillRect(event->rect(), background);

    int shipx = 50;
    int shipy = 50;
    int sizex = 200;
    int sizey = 200;
    int cx = sizex - shipx;
    int cy = sizey - shipy;

    // Center on ship
    QTransform transform;
    //transform.translate(cx, cy);
    //painter->setWorldTransform(transform);

    // Draw ship
    //painter->translate(shipx - this->ship.width()/2, shipy - this->ship.height()/2);
    painter->drawPixmap(200, 200, this->ship);

    painter->restore();
}
