#include <QDebug>
#include "universe.h"

Universe::Universe()
{
    this->timeAcceleration = 100;
}

void Universe::simulateStep(double deltaTime)
{
    // Loop through all bodies in Universe
    foreach (Body* b1, this->bodies)
    {
        // Acceleration from all bodies
        Vector accTotal;

        // Calculate force from Gravity from all other bodies
        foreach (Body* b2, this->bodies)
        {
            if ((b1 != b2) && b1->isAffectedByGravity()) {
                // Distance vector between bodies
                Vector delta = b2->getPosition() - b1->getPosition();

                // Magnitude of distance vector
                double r = delta.length();

                // Force of gravity
                double combinedMass = b1->getMass() * b2->getMass();
                double r2 = r * r;
                double f = G * (combinedMass / r2);

                // Acceleration due to gravity
                double a = f / b1->getMass();

                // Direction of acceleration
                Vector accDir = delta.normalized();

                // Total acceleration
                accTotal += accDir * a;
            }
        }

        // Set the acceleration
        b1->setAcceleration(accTotal);
    }

    foreach (Body* b1, this->bodies)
    {
        // Update the velocity and position
        if (b1->isMoveable())
        {
            b1->updateVelocity(b1->getAcceleration()*this->timeAcceleration*deltaTime);
            b1->updatePosition(b1->getVelocity()*this->timeAcceleration*deltaTime);
        }

        // Tick the body
        b1->tick(deltaTime);
    }
}

QList<Body*>& Universe::getBodies()
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
