#include <qmath.h>
#include "ship.h"

#define PI 3.14159265

Ship::Ship() :
    RenderBody()
{
    this->thrustPercentage = 0.0;
    this->thrust = 0.0;
}

Ship::Ship(QString asset, QString owner) :
    RenderBody(asset)
{
    this->owner = owner;
    this->thrustPercentage = 0.0;
    this->thrust = 0.0;
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

void Ship::calculateForces(QList<Body*> bodies, double timeAcceleration, double deltaTime)
{
    // Calculate force due to gravity on the Ship from all Server Bodies
    foreach (Body* b, bodies)
    {
        if (b->isServer())
        {
            // Distance Vector between Bodies
            Vector delta = b->getPosition() - this->getPosition();

            // Magnitude of distance Vector
            double r = delta.length();

            // Force of gravity
            double combinedMass = this->getMass() * b->getMass();
            double r2 = r * r;
            double f = G * (combinedMass / r2);

            // Add directional force to Body
            Vector force = delta.normalized() * f;
            this->pushForce(force);
        }
    }

    // Calculate force from thrust
    // Get normalized direction vector
    Vector dir;
    dir.setY(qCos(this->getRotation() * PI / 180));
    dir.setX(qSin(this->getRotation() * PI / 180));
    Vector force = dir * this->thrust;
    this->pushForce(force);

    // Update the velocity and position
    while(!this->isForcesEmpty())
    {
        // Calculate acceleration from the force
        Vector force = this->popForce();
        Vector acceleration = force / this->getMass();

        // Apply acceleration and velocity
        this->updateVelocity(acceleration * timeAcceleration * deltaTime);

        // Move me
        this->updatePosition(this->getVelocity() * timeAcceleration * deltaTime);
    }

    qDebug() << this->getPosition().getX() << " " << this->getPosition().getY();
}

void Ship::tick(double deltaTime)
{
    // Do not call parent
}

void Ship::increaseThrust(double deltaTime)
{
    if (this->thrustPercentage >= 0.0)
    {
        this->thrustPercentage = this->thrustPercentage + this->thrustRate * deltaTime;
    }

    if (this->thrustPercentage > 1.0)
    {
        this->thrustPercentage = 1.0;
    }

    this->thrust = this->thrustPercentage * this->maxThrust;
    qDebug() << this->thrustPercentage;
}

void Ship::decreaseThrust(double deltaTime)
{
    if (this->thrustPercentage <= 1.0)
    {
        this->thrustPercentage = this->thrustPercentage - this->thrustRate * deltaTime;
    }

    if (this->thrustPercentage < 0.0)
    {
        this->thrustPercentage = 0.0;
    }

    this->thrust = this->thrustPercentage * this->maxThrust;
    qDebug() << this->thrustPercentage;
}

void Ship::setMaxThrust(double maxThrust)
{
    this->maxThrust = maxThrust;
}
