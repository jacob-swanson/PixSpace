#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QList>
#include <QHash>
#include "body.h"
#include "shared_global.h"

class SHAREDSHARED_EXPORT DataManager
{
public:
    /**
     * @brief saveBodies Save given list of bodies
     */
    virtual void saveBodies(QList<Body*>) = 0;

    /**
     * @brief loadBodies Load a list of bodies
     * @return
     */
    virtual QList<Body*> loadBodies() = 0;

    /**
     * @brief saveConfig Save a map of settings
     */
    virtual void saveConfig(QHash<QString, QString>) = 0;

    /**
     * @brief loadConfig Load a map of settings
     * @return
     */
    virtual QHash<QString, QString> loadConfig() = 0;
};

#endif // DATAMANAGER_H
