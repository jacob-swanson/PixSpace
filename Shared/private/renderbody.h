#ifndef RENDERBODY_H
#define RENDERBODY_H

#include "body.h"
#include <QPixmap>
#include <QGraphicsItem>
#include <QString>

class RenderBody : public Body
{
public:
    RenderBody();
    void render();
    void createGraphic();
    void tick(double);
    void setSpritePath(QString spritePath);
    void collisionOccurred(RenderBody);
    QPixmap getGraphicsItem();
    void loadImageByteArray(QString bodyId);

private:
    QString spritePath;
    QByteArray rawSprite;
    QPixmap sprite;
    //QGraphicsItem *graphicsItem;
};

#endif // RENDERBODY_H
