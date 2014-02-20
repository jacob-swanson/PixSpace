#ifndef RENDERBODY_H
#define RENDERBODY_H

#include "body.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QImage>

class RenderBody : public Body
{
public:
    RenderBody();
    void render();
    void createGraphic();
    void tick(double);
    void setSpritePath(QString spritePath);
    void collisionOccurred(RenderBody);
    QGraphicsPixmapItem* getGraphicsItem();
    void loadImageByteArray(QString bodyId);
    void applyMask(QImage* image, QImage* mask);

private:
    QString spritePath;
    QByteArray rawSprite;
    QByteArray rawMask;
    QPixmap sprite;
    QGraphicsPixmapItem *spriteGraphicsItem;
};

#endif // RENDERBODY_H
