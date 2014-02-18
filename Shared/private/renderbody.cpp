#include "renderbody.h"

RenderBody::RenderBody(QString spritePath) :
    Body()
{
    this->setSpritePath(spritePath);
    createPixmap(); // this will load the graphic from spritePath

}

void RenderBody::render()
{


}

void RenderBody::createPixmap()
{
    //load pixmap from spritePath
    sprite = new QPixmap();
    sprite->load(spritePath);

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
