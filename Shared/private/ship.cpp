#include <qmath.h>
#include "ship.h"

#define PI 3.14159265

Ship::Ship() :
    RenderBody()
{
    this->throttlePercentage = 0.0;
    this->thrust = 0.0;
    this->thrustRate = 0.5;
}

void Ship::scheduleDelete()
{
    RenderBody::scheduleDelete();

    this->emitter->clear();
}

Ship::Ship(QString asset, QString owner) :
    RenderBody(asset)
{
    this->owner = owner;
    this->throttlePercentage = 0.0;
    this->thrust = 0.0;
    this->thrustRate = 0.5;
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
    this->throttlePercentage = json["throttle"].toDouble();
    this->maxThrust = json["maxThrust"].toDouble();
}

void Ship::write(QJsonObject &json) const
{
    RenderBody::write(json);

    json["owner"] = this->owner;
    json["throttle"] = this->throttlePercentage;
    json["maxThrust"] = this->maxThrust;
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

            // Collision occured if distance is less than the sum of the radiuses
            if (r < (b->getDiameter() / 2) + (this->getDiameter() / 2))
            {
                emit collisionOccured(b);
            }

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
}

void Ship::tick(double deltaTime)
{
    if (this->throttlePercentage > 0.0)
    {
        this->emitter->setEnabled(true);
    }
    else
    {
        this->emitter->setEnabled(false);
    }
    this->emitter->tick(deltaTime);
}

void Ship::increaseThrottle(double deltaTime)
{
    // Increase the thrustPercentage, and cap it at 1.0
    if (this->throttlePercentage >= 0.0)
    {
        this->throttlePercentage = this->throttlePercentage + this->thrustRate * deltaTime;
    }

    if (this->throttlePercentage > 1.0)
    {
        this->throttlePercentage = 1.0;
    }

    // Adjust the current amount of thrust
    this->thrust = this->throttlePercentage * this->maxThrust;
}

void Ship::decreaseThrottle(double deltaTime)
{
    // Decrease the thrustPercentage, and cap it at 0.0
    if (this->throttlePercentage <= 1.0)
    {
        this->throttlePercentage = this->throttlePercentage - this->thrustRate * deltaTime;
    }

    if (this->throttlePercentage < 0.0)
    {
        this->throttlePercentage = 0.0;
    }

    // Adjust the current amount of thrust
    this->thrust = this->throttlePercentage * this->maxThrust;
}

void Ship::setMaxThrust(double maxThrust)
{
    this->maxThrust = maxThrust;
}

bool Ship::createGraphic(QGraphicsScene *scene)
{
    bool ret = RenderBody::createGraphic(scene);
    this->emitter = new ParticleEmitter(scene, ParticleFlags::RANDOMIZE_INITIAL_ROTATION, this);

    this->emitter->setOffset(this->spriteGraphicsItem->boundingRect().height() / 2);
    this->emitter->setScaleCurve(0.3, 1.0, 0.0);
    this->emitter->setRedCurve(0.0, 1.0, 0.3);
    this->emitter->setBlueCurve(0.0, 0.0, 1.0);
    this->emitter->setGreenCurve(0.0, 0.6, 0.3);

    this->emitter->setParticleLife(2.0);
    this->emitter->setGenerationTime(0.1);
    return ret;
}

double Ship::getThrottle()
{
    return this->throttlePercentage;
}

void Ship::setThrottle(double throttle)
{
    this->throttlePercentage = throttle;

    // Adjust the current amount of thrust
    this->thrust = this->throttlePercentage * this->maxThrust;
}

