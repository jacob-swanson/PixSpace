#include "renderbody.h"

RenderBody::RenderBody(QString spritePath) :
    Body()
{
    this->setSpritePath(spritePath);
    createGraphic(); // this will load the graphic from spritePath

}

void RenderBody::render()
{


}

void RenderBody::createGraphic()
{
    //load pixmap from spritePath
    sprite = new QPixmap();
    sprite->load(spritePath);
    this->graphicsItem = new QGraphicsPixmapItem(*sprite);
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

void RenderBody::getGraphicsItem()
{

}
