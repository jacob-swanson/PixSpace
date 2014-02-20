#ifndef SIMPLEDATAMANAGER_H
#define SIMPLEDATAMANAGER_H
#include <QTextStream>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QByteArray>
#include "datamanager.h"
#include "shared_global.h"
#include <QMutex>

class SHAREDSHARED_EXPORT SimpleDataManager: public DataManager
{
public:
    static SimpleDataManager* instance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();

            if (!m_Instance)
            {
                m_Instance = new SimpleDataManager;
            }

            mutex.unlock();
        }

        return m_Instance;
    }

    /**
     * @brief saveBodies Output body parameters to command line
     */
    void saveBodies(QList<Body*>);

    /**
     * @brief loadBodies Returns an empty list
     * @return
     */
    QList<Body*> loadBodies();

    /**
     * @brief loadBodySprite Loads a sprite in the xpm format
     * @param id Id of the Sprite in the database
     * @param sprite Returning variable for the sprite
     * @return True if the art was loaded, false otherwise
     */
    bool loadBodySprite(QString id, QByteArray *sprite, QByteArray *mask);

    /**
     * @brief saveConfig Stub
     */
    void saveConfig(QHash<QString, QString>);

    /**
     * @brief loadConfig Returns an empty QMultiHash
     * @return
     */
    QHash<QString, QString> loadConfig();

private:
    SimpleDataManager() {}
//    SimpleDataManager(const SimpleDataManager &); // Hide copy constructor
//    SimpleDataManager& operator=(const SimpleDataManager &); // Hide assign operation

    static SimpleDataManager* m_Instance;

    QSqlDatabase db;

};

#endif // SIMPLEDATAMANAGER_H
