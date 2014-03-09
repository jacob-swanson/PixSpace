#include "ship.h"

Ship::Ship() :
    RenderBody()
{
}

Ship::Ship(QString asset, QString owner) :
    RenderBody(asset)
{
    this->owner = owner;
}

QString Ship::getOwner()
{
    return this->owner;
}

void Ship::setOwner(QString owner)
{
    this->owner = owner;
}

void Ship::read(const QJsonObject &json)
{
    RenderBody::read(json);

    this->owner = json["owner"].toString();
}

void Ship::write(QJsonObject &json) const
{
    RenderBody::write(json);

    json["owner"] = this->owner;
    json["type"] = QString("Ship");
}

void Ship::tick(double deltaTime)
{
    // Do not call parent
}
