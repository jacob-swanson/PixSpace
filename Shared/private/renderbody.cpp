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
    if (!dm.loadBodySprite(bodyId, &this->rawSprite, &this->rawMask))
    {
        // TODO: Exception
        qDebug() << "Could not load sprite";
    }
}

void RenderBody::createGraphic()
{

    QImage image;
    image.loadFromData(this->rawSprite);
    QImage mask;
    mask.loadFromData(this->rawMask);

    // Apply image filters
    if (image.size() != QSize(0, 0) && image.size() == mask.size())
    {
        QColor red;
        red.setRed(255);

        QColor blue;
        blue.setBlue(255);

        QColor green;
        green.setGreen(255);

        QColor primary;
        QColor secondary;
        QColor tertiary;

        // Generate colors
        primary.setRed(rand() % 256);
        primary.setBlue(rand() % 256);
        primary.setGreen(rand() % 256);
        secondary.setRed(rand() % 256);
        secondary.setBlue(rand() % 256);
        secondary.setGreen(rand() % 256);
        tertiary.setRed(rand() % 256);
        tertiary.setBlue(rand() % 256);
        tertiary.setGreen(rand() % 256);

        for (int x = 0; x < mask.size().width(); x++)
        {
            for (int y = 0; y < mask.size().height(); y++)
            {
                if (mask.pixel(x, y) == red.rgb())
                {
                    image.setPixel(x, y, primary.rgb());
                }
                else if (mask.pixel(x, y) == blue.rgb())
                {
                    image.setPixel(x, y, secondary.rgb());
                }
                else if (mask.pixel(x, y) == green.rgb())
                {
                    image.setPixel(x, y, tertiary.rgb());
                }
            }
        }
    }

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
