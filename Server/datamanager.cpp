#include "datamanager.h"
#include <RenderBody>
#include <QMessageBox>
#include <QDebug>

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

DataManager::~DataManager()
{
    this->instance()->drop();
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

void DataManager::saveBodies(QList<Body*> bodies) const
{
    QSqlQuery query;
    query.prepare("UPDATE body "
                  "SET positionx=?, positiony=?, velocityx=?, velocityy=? "
                  "WHERE id=?");
    foreach(Body* b, bodies)
    {
        // Output x and y position of a moveable body
        if (b->isMoveable())
        {
            query.addBindValue(b->getPosition().getX());
            query.addBindValue(b->getPosition().getY());
            query.addBindValue(b->getVelocity().getX());
            query.addBindValue(b->getVelocity().getY());
            query.addBindValue(b->getId());
            query.exec();
        }
    }
}

QList<Body*> DataManager::loadBodies() const
{
    QList<Body*> bodies;

    QSqlQuery query;
    query.prepare("SELECT id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID, "
                  "primaryMaskRed, primaryMaskBlue, primaryMaskGreen, secondaryMaskRed, secondaryMaskBlue, secondaryMaskGreen, tertiaryMaskRed, tertiaryMaskBlue, tertiaryMaskGreen "
                  "FROM body "
                  "WHERE 1");
    query.exec();

    // Load all bodies stored in DB
    while (query.next())
    {
        RenderBody* b1 = new RenderBody(query.value(8).toString());
        b1->setServer(true);
        b1->setID(query.value(0).toInt());
        b1->setMass(query.value(1).toDouble());
        b1->setPosition(query.value(2).toDouble(),  query.value(3).toDouble());
        b1->setVelocity(query.value(4).toDouble(), query.value(5).toDouble());
        b1->setRotationRate( query.value(6).toDouble());
        b1->setDiameter(query.value(7).toDouble());
        b1->setMasks(query.value(9).toInt(), query.value(10).toInt(), query.value(11).toInt(),
                     query.value(12).toInt(), query.value(13).toInt(), query.value(14).toInt(),
                     query.value(15).toInt(), query.value(16).toInt(), query.value(17).toInt());
        bodies.push_back(b1);
        // If Earth, set not moveable flag
        if (b1->getId() == 0)
        {
            b1->setMoveable(false);
        }
    }

    return bodies;
}


