#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <QList>

#include "body.h"
#include "shared_global.h"

#define G 6.67e-11

class SHAREDSHARED_EXPORT Universe
{
public:
    Universe();

    /**
     * @brief getBodies Get a QList of all of the bodies in the simulation
     * @return
     */
    QList<Body*>& getBodies();

    /**
     * @brief pushBodies Push a new body to the current list
     */
    void pushBodies(Body*);

    /**
     * @brief removeBody Remove a body from the Universe
     * @return Returns true on success; otherwise returns false
     */
    bool removeBody(Body*);

    /**
     * @brief setBodies Replace all of the current bodies
     */
    void setBodies(QList<Body*>);

    /**
     * @brief simulateStep Tick the simulation
     * @param deltaTime
     */
    void simulateStep(double deltaTime);

private:
    QList<Body*> bodies;    // List of all bodies in simulation
    double timeAcceleration;    // Amount to accelerate time by
};

#endif // UNIVERSE_H
