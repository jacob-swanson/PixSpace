#include "body.h"

Body::Body()
{
    // Initialize stock body
    this->moveable = true;
    this->affectedByGravity = true;
    rotation = 0;
    mass = 0;
    diameter = 0;
}

void Body::tick(double deltaTime)
{
    // Update the body
    // Nothing to be done
}

Vector Body::getPosition()
{
    // Return position vector
    return this->position;
}

double Body::getMass()
{
    // Return mass
    return this->mass;
}

void Body::setAcceleration(Vector acceleration)
{
    // Set acceleration vector
    this->acceleration = acceleration;
}

bool Body::isMoveable()
{
    // Return moveable
    return this->moveable;
}

void Body::updateVelocity(Vector velocity)
{
    // Add velocity to the current velocity
    this->velocity += velocity;
}

Vector Body::getAcceleration()
{
    // Get acceleration
    return this->acceleration;
}

void Body::updatePosition(Vector position)
{
    // Add position to current positions
    this->position += position;
}

Vector Body::getVelocity()
{
    // Get velocity
    return this->velocity;
}

bool Body::isAffectedByGravity()
{
    // Get affected by gravity
    return this->affectedByGravity;
}

void Body::setMass(double mass)
{
    // Set mass
    this->mass = mass;
}

void Body::setPosition(Vector position)
{
    // Set position
    this->position = position;
}

void Body::setPosition(double xpos, double ypos)
{
    // Set position with individual components
    this->position.setX(xpos);
    this->position.setY(ypos);
}

void Body::setMoveable(bool moveable)
{
    // Set moveable
    this->moveable = moveable;
}

void Body::setVelocity(double xvel, double yvel)
{
    // Set velocity using individual components
    this->velocity.setX(xvel);
    this->velocity.setY(yvel);
}

void Body::pushForce(Vector force)
{
    this->forces.push(force);
}

Vector Body::popForce()
{
    return this->forces.pop();
}

bool Body::isForcesEmpty()
{
    return this->forces.isEmpty();
}

void Body::setAffectedByGravity(bool affectedByGravity)
{
    this->affectedByGravity = affectedByGravity;
}
