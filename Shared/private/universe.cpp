#include "universe.h"

#include <QDebug>
Universe::Universe() :
    QObject(0)
{
    // Set 100,000x time acceleration
    this->timeAcceleration = 1;
}

void Universe::simulateStep(double deltaTime)
{
    // Loop through all Bodies in Universe calculating forces
    foreach (Body* b1, this->bodies)
    {
        if (b1->isServer() && b1->isAffectedByGravity())
        {
            // Calculate force from Gravity from all other Bodies
            foreach (Body* b2, this->bodies)
            {
                // If the Bodies are not the same, and the target Body is affected by gravity
                if ((b1 != b2) && b2->isServer()) {
                    // Distance Vector between Bodies
                    Vector delta = b2->getPosition() - b1->getPosition();

                    // Magnitude of distance Vector
                    double r = delta.length();

                    // Force of gravity
                    double combinedMass = b1->getMass() * b2->getMass();
                    double r2 = r * r;
                    double f = G * (combinedMass / r2);

                    // Add directional force to Body
                    Vector force = delta.normalized() * f;
                    b1->pushForce(force);
                }
            }
        }
    }

    // Loop through all Bodies again to update their position, velocity, and acceleration
    foreach (Body* b1, this->bodies)
    {
        // Only update server objects
        if (b1->isServer())
        {
            // Update the velocity and position
            while(!b1->isForcesEmpty())
            {
                // Calculate acceleration from the force
                Vector force = b1->popForce();
                Vector acceleration = force / b1->getMass();

                // Apply acceleration and velocity
                b1->updateVelocity(acceleration * this->timeAcceleration * deltaTime);

                // If the Body is moveable, move it
                if (b1->isMoveable())
                {
                    b1->updatePosition(b1->getVelocity() * this->timeAcceleration * deltaTime);
                }
            }

            // Do the Body's rotation
            b1->setRotation(b1->getRotation() + (b1->getRotationRate() * this->timeAcceleration * deltaTime));

            // Tick the body after it has been moved
            b1->tick(deltaTime);
        }
    }

    // Emit the finished signal
    emit stepFinished();
}

QList<Body*> Universe::getBodies() const
{
    // Return list of bodies
    return this->bodies;
}

void Universe::pushBodies(Body* body)
{
    // Add a new body to the back of the list
    this->bodies.push_back(body);
}

bool Universe::removeBody(Body* body)
{
    // Remove a body
    return this->bodies.removeOne(body);
}

void Universe::setBodies(QList<Body *> bodies)
{
    // Set bodies
    this->bodies = bodies;
}

void Universe::clearServerBodies()
{
    for (int i = 0; i < this->bodies.length(); i++)
    {
        if (this->bodies.at(i)->isServer())
        {
            this->bodies.removeAt(i);
        }
    }
}

void Universe::read(const QJsonObject &json, QString exclude)
{
    // Read in the Universe
    this->timeAcceleration = json["timeacceleration"].toDouble();

    QJsonArray bodyArray = json["bodies"].toArray();
    for (int i = 0; i < bodyArray.size(); i++)
    {
        QJsonObject bodyObject = bodyArray[i].toObject();

        // Find Body if exists
        Body* b = NULL;
        foreach(Body* searchBody, this->bodies)
        {
            if (searchBody->getId() == bodyObject["id"].toInt())
            {
                b = searchBody;
                break;
            }
        }

        if (b == NULL)
        {
            // New Body
            if (bodyObject["type"].toString() == "Body")
            {
                b = new Body();
                b->read(bodyObject);
                this->pushBodies(b);
            }
            else if (bodyObject["type"].toString() == "RenderBody")
            {
                b = new RenderBody();
                b->read(bodyObject);
                this->pushBodies(b);
            }
            else if (bodyObject["type"].toString() == "Ship")
            {
                b = new Ship();
                b->read(bodyObject);
                this->pushBodies(b);
            }
            else
            {
                QMessageBox errorBox;
                errorBox.setText("Could not load type: " + bodyObject["type"].toString());
                errorBox.exec();
            }
        }
        else
        {
            // Existing Body
            // Exclude the player's ship
            if (!bodyObject["owner"].isUndefined())
            {
                if (bodyObject["owner"].toString() != exclude)
                {
                    b->read(bodyObject);
                }
            }
            else
            {
                b->read(bodyObject);
            }
        }
    }

    foreach(Body* searchBody, this->bodies)
    {
        int num = -1;
        for (int i = 0; i < bodyArray.size(); i++)
        {
            if (searchBody->getId() == bodyArray[i].toObject()["id"].toInt())
            {
                num = i;
            }
        }

        if (num < 0)
        {
            this->removeBody(searchBody);
            emit bodyNotFound(searchBody);
        }
    }
}

void Universe::write(QJsonObject &json) const
{
    // Write to JSON
    json["timeacceleration"] = this->timeAcceleration;

    QJsonArray bodyArray;
    foreach(Body* b, this->bodies)
    {
        QJsonObject bodyObject;
        b->write(bodyObject);
        bodyArray.append(bodyObject);
    }
    json["bodies"] = bodyArray;

    json["type"] = QString("Universe");
}

double Universe::getTimeAcceleration()
{
    return this->timeAcceleration;
}

bool Universe::setTimeAcceleration(double timeAcceleration)
{
    // Check if legal value for time acceleration
    if (timeAcceleration == 1 || timeAcceleration == 5 || timeAcceleration == 10 || timeAcceleration == 50 || timeAcceleration == 100 || timeAcceleration == 1000
            || timeAcceleration == 10000 || timeAcceleration == 100000)
    {
        this->timeAcceleration = timeAcceleration;
        return true;
    }

    // If it isn't legal, return false
    return false;
}
