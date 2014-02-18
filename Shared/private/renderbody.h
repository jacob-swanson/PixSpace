#ifndef RENDERBODY_H
#define RENDERBODY_H

#include "body.h"
#include <QPixmap>

class RenderBody : public Body
{
public:
    RenderBody(QString spritePath);
    void render();
    void createPixmap();
    void tick(double);
    void setSpritePath(QString spritePath);
    void collisionOccurred(RenderBody);

private:
    QString spritePath;
    QPixmap *sprite;

};

#endif // RENDERBODY_H
