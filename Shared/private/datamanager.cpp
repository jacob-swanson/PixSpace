#include "datamanager.h"
#include "renderbody.h"

DataManager* DataManager::m_Instance = 0;

DataManager* DataManager::instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new DataManager;

        mutex.unlock();
    }

    return m_Instance;
}

void DataManager::drop()
{
    static QMutex mutex;
    mutex.lock();
    delete m_Instance;
    m_Instance = 0;
    mutex.unlock();
}

DataManager::DataManager()
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

bool DataManager::loadBodySprite(QString id, QByteArray *sprite, QByteArray *mask) const
{
    QSqlQuery query;
    query.prepare("SELECT sprite, mask "
                  "FROM body NATURAL JOIN sprite "
                  "WHERE id=?");
    query.bindValue(0, id);

    query.exec();

    if (query.next())
    {
        *sprite = query.value(0).toByteArray();
        *mask = query.value(1).toByteArray();

        return true;
    }

    qDebug() << "Sprite for: " << id << " not found in database.";

    return false;
}

void DataManager::saveBodies(QList<Body*> bodies) const
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

QList<Body*> DataManager::loadBodies() const
{
    // Create Moon and Earth
    QList<Body*> bodies;

    RenderBody* b1 = new RenderBody("Moon");
    RenderBody* b2 = new RenderBody("WaterPlanet");
    b1->setServer(true);
    b2->setServer(true);

    // Moon
    b1->setMass(7.3459e22);
    b1->setPosition(3.8e8, 0);
    b1->setVelocity(0, 1023);
    b1->setRotationRate(10);

    // Earth
    b2->setMass(5.9721986e24);
    b2->setPosition(0, 0);
    b2->setMoveable(false);
    b2->setRotationRate(-20);

    // Add Earth and Sun to list
    bodies.push_back(b1);
    bodies.push_back(b2);

    return bodies;
}


