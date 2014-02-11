#ifndef BODY_H
#define BODY_H
#include <QString>
#include <QStack>
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
     * @brief updatePosition Add position to the current position (Units: m)
     * @param position
     */
    void updatePosition(Vector position);

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

    /**
     * @brief getVelocity Get the velocity of the Body (Units: m/s)
     * @return
     */
    Vector getVelocity();

    /**
     * @brief updateVelocity Add velocity to the current amount (Units: m/s)
     * @param velocity
     */
    void updateVelocity(Vector velocity);

    /**
     * @brief setVelocity Set Body's velocity by using components (Units: m/s)
     * @param xvel
     * @param yvel
     */
    void setVelocity(double xvel, double yvel);

    /**
     * @brief getAcceleration Get the acceleration of the Body (Units: m/s^2)
     * @return
     */
    Vector getAcceleration();

    /**
     * @brief setAcceleration Set the acceleration of the Body (Units: m/s^2)
     * @param acceleration
     */
    void setAcceleration(Vector acceleration);

    /**
     * @brief getMass Get the mass of the body (Units: kg)
     * @return
     */
    double getMass();

    /**
     * @brief setMass Set the mass of the body (Units: kg)
     * @param mass
     */
    void setMass(double mass);

    /**
     * @brief isMoveable True if the body will be moved by gravity; otherwise false.
     * @return
     */
    bool isMoveable();

    /**
     * @brief setMoveable If true, the Body's position will not be affected in the Universe's calculation
     * @param moveable
     */
    void setMoveable(bool moveable);

    /**
     * @brief isAffectedByGravity True if gravity affects the body, false otherwise
     * @return
     */
    bool isAffectedByGravity();

    /**
     * @brief setAffectedByGravity Set true to have gravity forces calculated by Universe
     */
    void setAffectedByGravity(bool affectedByGravity);

    /**
     * @brief pushForce Push a new force onto the Stack (Units: N)
     * @param force
     */
    void pushForce(Vector force);

    /**
     * @brief popForce Pop the top force and return it (Units: N)
     * @return
     */
    Vector popForce();

    /**
     * @brief isForcesEmpty True if the Stack of forces is empty, false otherwise
     * @return
     */
    bool isForcesEmpty();

protected:
    Vector position;
    Vector velocity;
    Vector acceleration;
    QStack<Vector> forces;
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
