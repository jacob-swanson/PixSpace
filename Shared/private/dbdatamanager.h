#ifndef DBDATAMANAGER_H
#define DBDATAMANAGER_H
#include <QMutex>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>

class DBDataManager
{
public:
    static DBDataManager* instance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();

            if (!m_Instance)
                m_Instance = new DBDataManager;

            mutex.unlock();
        }

        return m_Instance;
    }

    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }

    /**
     * @brief loadBodySprite Loads a sprite in the xpm format
     * @param id Id of the Sprite in the database
     * @param sprite Returning variable for the sprite
     * @return True if the art was loaded, false otherwise
     */
    bool loadBodySprite(QString id, QByteArray *sprite, QByteArray *mask);

private:
    DBDataManager() {
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

    DBDataManager(const DBDataManager &); // hide copy constructor
    DBDataManager& operator=(const DBDataManager &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident

    static DBDataManager* m_Instance;
    QSqlDatabase db;
};

#endif // DBDATAMANAGER_H
