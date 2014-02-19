#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include "simpledatamanager.h"

SimpleDataManager::SimpleDataManager()
{
    db = QSqlDatabase::addDatabase( "QMYSQL3" );
    db.setHostName( "localhost" );
    db.setPort(3306);
    db.setDatabaseName( "pixspace" );
    db.setUserName( "pixspace" );
    db.setPassword( "pixspace" );

    if ( !db.open() )
    {
        qDebug() << db.lastError();
        qDebug() << "Error: Unable to connect due to above error";
    }
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
                //qDebug() << qSetRealNumberPrecision(10) << b->getPosition().getX() << " " << b->getPosition().getY();// << " " << b->getAcceleration().getX() << " " << b->getAcceleration().getY() << " " << b->getVelocity().getX() << " " << b->getVelocity().getY();
                out << qSetRealNumberPrecision(10) << b->getPosition().getX() << " " << b->getPosition().getY() << "\n";// << " " << b->getAcceleration().getX() << " " << b->getAcceleration().getY() << " " << b->getVelocity().getX() << " " << b->getVelocity().getY();
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

bool SimpleDataManager::loadBodySprite(QString id, QString *sprite)
{
    QSqlQuery query;
    query.prepare("SELECT sprite "
                  "FROM body NATURAL JOIN sprite "
                  "WHERE id=?");
    query.bindValue(0, id);

    query.exec();

    if (query.next())
    {
        *sprite = query.value(0).toString();

        return true;
    }

    qDebug() << "Sprite for: " << id << " not found in database.";

    return false;
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
