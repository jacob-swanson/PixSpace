#include "dbdatamanager.h"

DBDataManager* DBDataManager::m_Instance = 0;

bool DBDataManager::loadBodySprite(QString id, QByteArray *sprite, QByteArray *mask)
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
