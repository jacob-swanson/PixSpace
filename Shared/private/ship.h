#ifndef SHIP_H
#define SHIP_H

#include "renderbody.h"

class Ship : public RenderBody
{
public:
    /**
     * @brief Ship Initialize default Ship
     */
    Ship();

    /**
     * @brief Ship Initialize a Ship with an owner
     * @param owner
     */
    Ship(QString asset, QString owner);

    /**
     * @brief setOwner Set the owner (username) of the Ship
     * @param owner
     */
    void setOwner(QString owner);

    /**
     * @brief getOwner Get the owner (username) of the Ship
     * @return
     */
    QString getOwner();

    /**
     * @brief read Read in from json
     * @param json
     */
    void read(const QJsonObject &json);

    /**
     * @brief write Write to json
     * @param json
     */
    void write(QJsonObject &json) const;

    /**
     * @brief tick Do any ship updates here
     * @param deltaTime
     */
    void tick(double deltaTime);

private:
    QString owner;
};

#endif // SHIP_H
