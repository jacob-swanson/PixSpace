#ifndef BODY_H
#define BODY_H
#include <QString>
#include "vector.h"
#include "shared_global.h"

class SHAREDSHARED_EXPORT Body
{
public:
    Body();

    /**
     * @brief tick Run any body specific code
     * @param deltaTime Time since the last tick
     */
    void tick(double deltaTime);

    /**
     * @brief getPosition Get the position of the Body (Units: meters)
     * @return
     */
    Vector getPosition();

    /**
     * @brief getMass Get the mass of the body (Units: kg)
     * @return
     */
    double getMass();

    /**
     * @brief setAcceleration Set the acceleration of the Body (Units: m/s^2)
     * @param acceleration
     */
    void setAcceleration(Vector acceleration);

    /**
     * @brief isMoveable True if the body will be moved by gravity; otherwise false.
     * @return
     */
    bool isMoveable();

    /**
     * @brief updateVelocity Add velocity to the current amount (Units: m/s)
     * @param velocity
     */
    void updateVelocity(Vector velocity);

    /**
     * @brief getAcceleration Get the acceleration of the Body (Units: m/s^2)
     * @return
     */
    Vector getAcceleration();

    /**
     * @brief updatePosition Add position to the current position (Units: m)
     * @param position
     */
    void updatePosition(Vector position);

    /**
     * @brief getVelocity Get the velocity of the Body (Units: m/s)
     * @return
     */
    Vector getVelocity();

    /**
     * @brief isAffectedByGravity True if gravity affects the body, false otherwise
     * @return
     */
    bool isAffectedByGravity();

    /**
     * @brief setMass Set the mass of the body (Units: kg)
     * @param mass
     */
    void setMass(double mass);

    /**
     * @brief setPosition Set the position of the body (Units: m)
     * @param position
     */
    void setPosition(Vector position);

    /**
     * @brief setPosition Set the position of the body (Units: m)
     * @param xpos
     * @param ypos
     */
    void setPosition(double xpos, double ypos);

    void setMoveable(bool moveable);

    void setVelocity(double xvel, double yvel);


protected:
    Vector position;
    Vector velocity;
    Vector acceleration;
    double rotation;
    double mass;
    double diameter;
    bool moveable;
    QString name;
    bool affectedByGravity;

private:
    QString id;
};

#endif // BODY_H
