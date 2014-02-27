#include "renderbody.h"

RenderBody::RenderBody() :
    Body()
{
}

void RenderBody::loadImageByteArray(QString bodyId)
{
    // Database access here
    if (!DataManager::instance()->loadBodySprite(bodyId, &this->rawSprite, &this->rawMask))
    {
        // TODO: Exception
        qDebug() << "Could not load sprite";
    }
}

void RenderBody::createGraphic()
{
    // Create QImages so they can be manipulated pixel by pixel
    QImage image;
    image.loadFromData(this->rawSprite);
    QImage mask;
    mask.loadFromData(this->rawMask);

    // Apply image filters
    this->applyMask(&image, &mask);

    // Create the pixmap and graphics item for rendering
    this->sprite.convertFromImage(image);
    this->spriteGraphicsItem = new QGraphicsPixmapItem(this->sprite);
}

void RenderBody::applyMask(QImage* image, QImage* mask)
{
    // Image must have a size, and the mask must be the same size
    if (image->size() != QSize(0, 0) && image->size() == mask->size())
    {
        // Colors in mask to replace in image
        // Red, Blue, Green
        QColor primaryMask;
        primaryMask.setRed(255);
        QColor secondaryMask;
        secondaryMask.setBlue(255);
        QColor tertiaryMask;
        tertiaryMask.setGreen(255);

        // Autogenerated colors
        QColor primary;
        QColor secondary;
        QColor tertiary;

        // Generate random colors using RGB values from 0 to 255
        primary.setRed(rand() % 256);
        primary.setBlue(rand() % 256);
        primary.setGreen(rand() % 256);
        secondary.setRed(rand() % 256);
        secondary.setBlue(rand() % 256);
        secondary.setGreen(rand() % 256);
        tertiary.setRed(rand() % 256);
        tertiary.setBlue(rand() % 256);
        tertiary.setGreen(rand() % 256);

        // Loop through each pixel in the images
        for (int x = 0; x < mask->size().width(); x++)
        {
            for (int y = 0; y < mask->size().height(); y++)
            {
                // For red in mask, replace with primary
                if (mask->pixel(x, y) == primaryMask.rgb())
                {
                    image->setPixel(x, y, primary.rgb());
                }
                // For blue in mask, replace with secondary
                else if (mask->pixel(x, y) == secondaryMask.rgb())
                {
                    image->setPixel(x, y, secondary.rgb());
                }
                // For green in mask, replace with tertiary
                else if (mask->pixel(x, y) == tertiaryMask.rgb())
                {
                    image->setPixel(x, y, tertiary.rgb());
                }
            }
        }
    }
}

void RenderBody::tick(double deltaTime)
{
    // Call the parent version of tick
    Body::tick(deltaTime);
}

QGraphicsPixmapItem* RenderBody::getGraphicsItem()
{
    // Get the graphics item
    return this->spriteGraphicsItem;
}

void RenderBody::read(const QJsonObject &json)
{
    // Read in a JSON object
    Body::read(json);

    this->rawSprite = QByteArray::fromBase64(json["sprite"].toString().toLocal8Bit());
    this->rawMask = QByteArray::fromBase64(json["mask"].toString().toLocal8Bit());
}

void RenderBody::write(QJsonObject &json) const
{
    // Write to a JSON object
    Body::write(json);

    json["sprite"] = QString(this->rawSprite.toBase64());
    json["mask"] = QString(this->rawMask.toBase64());
}
