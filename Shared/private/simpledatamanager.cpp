#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "simpledatamanager.h"

SimpleDataManager::SimpleDataManager()
{

}

void SimpleDataManager::saveBodies(QList<Body*> bodies)
{
    QFile logFile("orbit.data");

    if (logFile.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream out(&logFile);

        foreach(Body* b, bodies)
        {
            // Output x and y position of a moveable body
            if (b->isMoveable())
            {
                out << qSetRealNumberPrecision(10) << b->getPosition().getX() << " " << b->getPosition().getY();// << " " << b->getAcceleration().getX() << " " << b->getAcceleration().getY() << " " << b->getVelocity().getX() << " " << b->getVelocity().getY();
            }
        }
    }

}

QList<Body*> SimpleDataManager::loadBodies()
{
    // Create Moon and Earth
    QList<Body*> bodies;

    Body* b1 = new Body();
    Body* b2 = new Body();

    // Moon
    b1->setMass(7.3459e22);
    b1->setPosition(3.8e8, 0);
    b1->setVelocity(0, 1023);

    // Earth
    b2->setMass(5.9721986e24);
    b2->setPosition(0, 0);
    b2->setMoveable(false);

    // Add Earth and Sun to list
    bodies.push_back(b1);
    bodies.push_back(b2);

    return bodies;
}

void SimpleDataManager::saveConfig(QHash<QString, QString>)
{

}

QHash<QString, QString> SimpleDataManager::loadConfig()
{
    // Return empty config
    QMultiHash<QString, QString> config;
    return config;
}
