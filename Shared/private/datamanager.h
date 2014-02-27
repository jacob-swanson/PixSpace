#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QMutex>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>

#include "body.h"
#include "shared_global.h"

/**
 * @brief The DataManager class Manages saving and loading
 */
class SHAREDSHARED_EXPORT DataManager
{
public:
    /**
     * @brief instance Get the singleton instance
     * @return
     */
    static DataManager* instance();

    /**
     * @brief drop Destroy the singleton instance
     */
    static void drop();

    /**
     * @brief loadBodySprite Loads the data for a sprite
     * @param id Id of the Sprite in the database
     * @param sprite Returning variable for the sprite
     * @return True if the art was loaded, false otherwise
     */
    bool loadBodySprite(QString id, QByteArray *sprite, QByteArray *mask) const;

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
