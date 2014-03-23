#include "body.h"

Body::Body(QObject *parent) :
    QObject(parent)
{
    // Initialize stock body
    this->moveable = true;
    this->affectedByGravity = true;
    rotation = 0;
    mass = 0;
    diameter = 0;
    rotationRate = 0;

    this->id = qrand();
    this->serverBody = false;
}

void Body::tick(double deltaTime)
{
    // Update the body
}

Vector Body::getPosition() const
{
    // Return position vector
    return this->position;
}

double Body::getMass() const
{
    // Return mass
    return this->mass;
}

void Body::setAcceleration(Vector acceleration)
{
    // Set acceleration vector
    this->acceleration = acceleration;
}

bool Body::isMoveable() const
{
    // Return moveable
    return this->moveable;
}

void Body::updateVelocity(Vector velocity)
{
    // Add velocity to the current velocity
    this->velocity += velocity;
}

Vector Body::getAcceleration() const
{
    // Get acceleration
    return this->acceleration;
}

void Body::updatePosition(Vector position)
{
    // Add position to current positions
    this->position += position;
}

Vector Body::getVelocity() const
{
    // Get velocity
    return this->velocity;
}

bool Body::isAffectedByGravity() const
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

void Body::setVelocity(Vector velocity)
{
    // Set velocity
    this->velocity = velocity;
}

void Body::pushForce(Vector force)
{
    // Push a force onto the stack
    this->forces.push(force);
}

Vector Body::popForce()
{
    // Pop a force off of the stack
    return this->forces.pop();
}

bool Body::isForcesEmpty() const
{
    // Check if the forces stack is empty
    return this->forces.isEmpty();
}

void Body::setAffectedByGravity(bool affectedByGravity)
{
    // Set affectedByGravity
    this->affectedByGravity = affectedByGravity;
}

int Body::getId() const
{
    // Get the id
    return this->id;
}

void Body::setDiameter(double diameter)
{
    // Set the diameter
    this->diameter = diameter;
}

double Body::getDiameter() const
{
    // Get the diameter
    return this->diameter;
}

void Body::setRotation(double rotation)
{
    // Set the rotation
    this->rotation = rotation;
}

double Body::getRotation() const
{
    // Get the rotation
    return this->rotation;
}

void Body::setServer(bool isServer)
{
    this->serverBody = isServer;
}

bool Body::isServer()
{
    return this->serverBody;
}

double Body::getRotationRate()
{
    return this->rotationRate;
}

void Body::setRotationRate(double rotationRate)
{
    this->rotationRate = rotationRate;
}

void Body::read(const QJsonObject &json)
{
    // Read in parameters from a JSON object
    this->position.read(json["position"].toObject());
    this->velocity.read(json["velocity"].toObject());
    this->acceleration.read(json["acceleration"].toObject());

    this->setAffectedByGravity(json["gravity"].toBool());
    this->setMass(json["mass"].toDouble());
    this->setMoveable(json["moveable"].toBool());
    this->id = json["id"].toInt();
    this->serverBody = json["server"].toBool();
    this->rotationRate = json["rotationRate"].toDouble();

    this->setDiameter(json["diameter"].toDouble());
    this->setRotation(json["rotation"].toDouble());
}

void Body::write(QJsonObject &json) const
{
    // Write out "this" to a JSON object
    QJsonObject positionObject;
    this->position.write(positionObject);

    QJsonObject velocityObject;
    this->velocity.write(velocityObject);

    QJsonObject accelerationObject;
    this->acceleration.write(accelerationObject);

    json["position"] = positionObject;
    json["velocity"] = velocityObject;
    json["acceleration"] = accelerationObject;

    json["gravity"] = this->affectedByGravity;
    json["mass"] = this->mass;
    json["moveable"] = this->moveable;
    json["diameter"] = this->diameter;
    json["rotation"] = this->rotation;
    json["id"] = this->id;
    json["server"] = this->serverBody;
    json["rotationRate"] = this->rotationRate;

    json["type"] = QString("Body");
}

void Body::scheduleDelete()
{
    this->deleteLater();
}
