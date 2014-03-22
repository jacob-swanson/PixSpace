#include "particle.h"

Particle::Particle(QGraphicsScene *scene, QString resource, QObject *parent) :
    QObject(parent)
{
    this->scene = scene;
    map = new QPixmap(resource);
    this->graphicsItem = new QGraphicsPixmapItem(*this->map);
    this->scene->addItem(this->graphicsItem);
}


void Particle::remove()
{
    // Remove the item from the scene
    this->scene->removeItem(this->graphicsItem);
}

double Particle::addLife(double deltaTime)
{
    this->life += deltaTime;

    return this->life;
}

void Particle::addPosition(Vector position)
{
    this->graphicsItem->setPos(
                this->graphicsItem->x() + position.getX(),
                this->graphicsItem->y() + position.getY()
                );
}

double Particle::getLife()
{
    return this->life;
}

void Particle::setScale(double scale)
{
    this->graphicsItem->setScale(scale);
}

void Particle::setColor(QColor color)
{
    this->map->fill(color);
    this->graphicsItem->setPixmap(*this->map);
}

void Particle::setRotation(double rotation)
{
    this->graphicsItem->setRotation(rotation);
}
