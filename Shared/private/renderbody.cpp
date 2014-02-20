#include "renderbody.h"
#include "simpledatamanager.h"
#include <QDebug>

RenderBody::RenderBody() :
    Body()
{
}

void RenderBody::render()
{

}

void RenderBody::loadImageByteArray(QString bodyId)
{
    SimpleDataManager dm;
    if (!dm.loadBodySprite(bodyId, &this->rawSprite))
    {
        // TODO: Exception
        qDebug() << "Could not load sprite";
    }
}

void RenderBody::createGraphic()
{

    QImage image;
    image.loadFromData(this->rawSprite);

    // Apply image filters
//    QColor black;
//    QColor red;

//    black.setBlue(0);
//    black.setRed(0);
//    black.setGreen(0);

//    red.setRed(0);
//    red.setBlue(255);
//    red.setGreen(0);

//    for (int x = 0; x < image.size().width(); x++) {
//        for (int y = 0; y < image.size().height(); y++) {
//            if (image.pixel(x, y) == black.rgb()) {
//                image.setPixel(x, y, red.rgb());
//            }
//        }
//    }

    this->sprite.convertFromImage(image);
    this->spriteGraphicsItem = new QGraphicsPixmapItem(this->sprite);
}

void RenderBody::tick(double)
{

}


void RenderBody::setSpritePath(QString spritePath)
{
    this->spritePath = spritePath;
}

void RenderBody::collisionOccurred(RenderBody)
{

}

QGraphicsPixmapItem* RenderBody::getGraphicsItem()
{
    return this->spriteGraphicsItem;
}
