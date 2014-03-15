#ifndef SHIP_H
#define SHIP_H

#include "renderbody.h"
#include "universe.h"

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

    /**
     * @brief calculateForces Calculate forces due to gravity on the Ship
     * @param bodies Universe's Bodies
     */
    void calculateForces(QList<Body*> bodies, double timeAcceleration, double deltaTime);

    /**
     * @brief increaseThrust Increase the thrust percentage
     * @param deltaTime
     */
    void increaseThrust(double deltaTime);

    /**
     * @brief decreaseThrust Decrease the thrust percentage
     * @param deltaTime
     */
    void decreaseThrust(double deltaTime);

    /**
     * @brief setThrust Set the maximum thrust for the ship (Units: N)
     * @param thrust
     */
    void setMaxThrust(double maxThrust);

private:
    QString owner;
    double thrustPercentage;
    double maxThrust;
    double thrust;
    const static double thrustRate = 0.5;
};

#endif // SHIP_H
