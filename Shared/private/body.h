#ifndef BODY_H
#define BODY_H

#include <QString>
#include <QStack>
#include <QJsonObject>

#include "vector.h"
#include "shared_global.h"

/**
 * @brief The Body class Base class for Bodies in the simulation
 */
class SHAREDSHARED_EXPORT Body
{
public:
    /**
     * @brief Body Initialize a Body with default values (usually 0)
     */
    Body();

    /**
     * @brief tick Stub function to be implemented by a child class
     * @param deltaTime Time since the last tick
     */
    void tick(double deltaTime);

    /**
     * @brief getPosition Get the position in the simulation (Units: meters)
     * @return
     */
    Vector getPosition();

    /**
     * @brief updatePosition Add position to the current position in the simulation (Units: m)
     * @param position
     */
    void updatePosition(Vector position);

    /**
     * @brief setPosition Set the position in the simulation (Units: m)
     * @param position
     */
    void setPosition(Vector position);

    /**
     * @brief setPosition Set the position in the simulation (Units: m)
     * @param xpos
     * @param ypos
     */
    void setPosition(double xpos, double ypos);

    /**
     * @brief getVelocity Get the velocity in the simulation (Units: m/s)
     * @return
     */
    Vector getVelocity();

    /**
     * @brief updateVelocity Add velocity to the current amount in the simulation (Units: m/s)
     * @param velocity
     */
    void updateVelocity(Vector velocity);

    /**
     * @brief setVelocity Set Body's velocity in the simulation (Units: m/s)
     * @param xvel
     * @param yvel
     */
    void setVelocity(double xvel, double yvel);

    /**
     * @brief setVelocity Set Body's velocity in the simulation (Units: m/s)
     * @param velocity
     */
    void setVelocity(Vector velocity);

    /**
     * @brief getAcceleration Get the acceleration in the simulation (Units: m/s^2)
     * @return
     */
    Vector getAcceleration();

    /**
     * @brief setAcceleration Set the acceleration in the simulation (Units: m/s^2)
     * @param acceleration
     */
    void setAcceleration(Vector acceleration);

    /**
     * @brief getMass Get the mass in the simulation (Units: kg)
     * @return
     */
    double getMass();

    /**
     * @brief setMass Set the mass in the simulation (Units: kg)
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

    /**
     * @brief getId Get the identifier
     * @return
     */
    QString getId();

    /**
     * @brief setDiameter Set the diameter (Units: m)
     * @return
     */
    void setDiameter(double diameter);

    /**
     * @brief getDiameter Get the diameter (Units: m)
     * @return
     */
    double getDiameter();

    /**
     * @brief setRotation Set the rotation (Units: Degrees)
     * @return
     */
    void setRotation(double rotation);

    /**
     * @brief getRotation Get the rotation (Units: Degrees)
     * @return
     */
    double getRotation();

    /**
     * @brief read Read in from the given JSON object
     * @param json
     */
    void read(const QJsonObject &json);

    /**
     * @brief write Write to the given JSON object
     * @param json
     */
    void write(QJsonObject &json) const;

protected:
    // Simulation variables
    Vector position;
    Vector velocity;
    Vector acceleration;
    QStack<Vector> forces;
    double mass;
    bool affectedByGravity;
    bool moveable;

    // Other variables
    double rotation;
    double diameter;
    QString name;

private:
    QString id;
};

#endif // BODY_H
