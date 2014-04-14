#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QMutex>
#include <QString>
#include <QDebug>
#include <QHash>
#include <QFile>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <Body>

/**
 * @brief The DataManager class Manages saving and loading
 */
class DataManager
{
public:
    /**
     * @brief instance Get the singleton instance
     * @return
     */
    static DataManager* instance();

    /**
      * @breif ~DataManager drops the database connection
      */
    ~DataManager();

    /**
     * @brief drop Destroy the singleton instance
     */
    static void drop();

    /**
     * @brief saveBodies Save a list of Bodies
     * @param bodies
     */
    void saveBodies(QList<Body*> bodies) const;

    /**
     * @brief loadBodies Load a list of Bodies
     * @return
     */
    QList<Body*> loadBodies() const;

    /**
     * @brief setHostName Sets the database server's hostname/ip
     * @param hostName Hostname/Ip address
     */
    void setHostName(QString hostName);

    /**
     * @brief setPort Sets the database's port
     * @param portNum Port number for the database
     */
    void setPort(int portNum);

    /**
     * @brief setDatabaseName Sets the dabase's name
     * @param dbName Name of the database
     */
    void setDatabaseName(QString dbName);

    /**
     * @brief DsetUserName Sets the user name for the DB access
     * @param dbUser String of the username
     */
    void setUserName(QString dbUser);

    /**
     * @brief setPassword Sets the password for the user for the DB
     * @param password Password for the user
     */
    void setPassword(QString password);

    /**
     * @brief connect Connects to DB, returns false on failure
     * @return Bool to indicate success or failure
     */
    bool connect();

    /**
     * @brief getLastError Returns the last DB error
     * @return QString
     */
    QString getLastError();

    /**
     * @brief getHostName Gets hostname
     * @return QString
     */
    QString getHostName();

    /**
     * @brief getPort Get port number
     * @return int
     */
    int getPort();

    /**
     * @brief getDatabaseName Gets the database name
     * @return QString
     */
    QString getDatabaseName();

    /**
     * @brief getUserName Get the username for DB
     * @return QString
     */
    QString getUserName();


private:
    // Hide constructor
    DataManager();

    // Hide copy constructor
    DataManager(const DataManager &);

    // High assignment operator
    DataManager& operator=(const DataManager &);

    static DataManager* m_Instance;
    QSqlDatabase db;
};

#endif // DATAMANAGER_H
