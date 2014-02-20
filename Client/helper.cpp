#include "helper.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>
#include <vector>
#include <QColor>
#include "../Shared/SimpleDataManager"

Helper::Helper()
{
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    background = QBrush(QColor(Qt::black));

    QByteArray sprite;
    SimpleDataManager dm;
    if (dm.loadBodySprite(QString("a"), &sprite))
    {
       // qDebug() << sprite;
    }
    else
    {
        qDebug() << "Could not load sprite";
    }
    QColor black;
    QColor red;

    black.setBlue(0);
    black.setRed(0);
    black.setGreen(0);

    red.setRed(0);
    red.setBlue(255);
    red.setGreen(0);

    QImage image;
    image.loadFromData(sprite);
    for (int x = 0; x < image.size().width(); x++) {
        for (int y = 0; y < image.size().height(); y++) {
            if (image.pixel(x, y) == black.rgb()) {
                image.setPixel(x, y, red.rgb());
            }
        }
    }
    this->ship.convertFromImage(image);

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
