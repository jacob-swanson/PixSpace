#include "datamanager.h"
#include <RenderBody>

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
}

void DataManager::setHostName(QString hostName)
{
    this->db.setHostName(hostName);
}

void DataManager::setPort(int portNum)
{
    this->db.setPort(portNum);
}

void DataManager::setDatabaseName(QString dbName)
{
    this->db.setDatabaseName(dbName);
}

void DataManager::setUserName(QString dbUser)
{
    this->db.setUserName(dbUser);
}

void DataManager::setPassword(QString password)
{
    this->db.setPassword(password);
}

QString DataManager::getHostName()
{
    return db.hostName();
}

int DataManager::getPort()
{
    return db.port();
}

QString DataManager::getDatabaseName()
{
    return db.databaseName();
}

QString DataManager::getUserName()
{
    return db.userName();
}

QString DataManager::getLastError()
{
    return db.lastError().text();
}

bool DataManager::connect()
{
    return db.open();
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
    b1->setRotationRate(-0.00015);
    b1->setDiameter(3.4e6);

    // Earth
    b2->setMass(5.9721986e24);
    b2->setPosition(0, 0);
    b2->setMoveable(false);
    b2->setRotationRate(0.0001);
    b2->setDiameter(1.27e7);

    // Add Earth and Sun to list
    //bodies.push_back(b1);
    //bodies.push_back(b2);

    return bodies;
}

void DataManager::parseconfig()
{
    QFile file("config.dat");
        QHash<QString, QString> config;

        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "can't open file for reading" << qPrintable(file.errorString());
        }
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList tokens = line.split(":");
            config.insert(tokens[0],tokens[1]);
        }

        //to test that values were stored in QHash properly
            QHashIterator<QString, QString> iter(config);
            while (iter.hasNext())
            {
                iter.next();
                qDebug() << iter.key() << iter.value();
            }

        file.close();

}

void DataManager::createconfig()
{
        QHash<QString, QString> config;

        config.insert("hostname", "localhost");
        config.insert("port", "3306");
        config.insert("dbname", "pixspace");
        config.insert("username", "pixspace");
        config.insert("password", "pixspace");

        QFile file("config.dat");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "can't open file for writing" << qPrintable(file.errorString());
        }
        QTextStream out(&file);
        QHashIterator<QString, QString> iter(config);
        while (iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << iter.value();
            out << iter.key() << ":" << iter.value() << endl;
        }
        file.flush();
        file.close();
}
