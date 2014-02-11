#ifndef SIMPLEDATAMANAGER_H
#define SIMPLEDATAMANAGER_H
#include <QTextStream>
#include "datamanager.h"
#include "shared_global.h"

class SHAREDSHARED_EXPORT SimpleDataManager: public DataManager
{
public:
    SimpleDataManager();

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
     * @brief saveConfig Stub
     */
    void saveConfig(QHash<QString, QString>);

    /**
     * @brief loadConfig Returns an empty QMultiHash
     * @return
     */
    QHash<QString, QString> loadConfig();
};

#endif // SIMPLEDATAMANAGER_H
