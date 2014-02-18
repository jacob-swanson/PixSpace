#ifndef RENDERBODY_H
#define RENDERBODY_H

#include "body.h"
#include <QPixmap>
#include <QGraphicsItem>

class RenderBody : public Body
{
public:
    RenderBody(QString spritePath);
    void render();
    void createGraphic();
    void tick(double);
    void setSpritePath(QString spritePath);
    void collisionOccurred(RenderBody);
    void getGraphicsItem();

private:
    QString spritePath;
    QPixmap *sprite;
    QGraphicsItem *graphicsItem;
};

#endif // RENDERBODY_H
