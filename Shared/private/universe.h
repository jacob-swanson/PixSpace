#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QList>
#include <QJsonArray>
#include <QObject>

#include "body.h"
#include "shared_global.h"

// Gravitational constant, G
#define G 6.67e-11

/**
 * @brief The Universe class Runs simulation on all given Bodies
 */
class SHAREDSHARED_EXPORT Universe : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Universe Create an empty Universe
     */
    Universe();

    /**
     * @brief getBodies Get a QList of all of the Bodies in the simulation
     * @return
     */
    QList<Body*> getBodies() const;

    /**
     * @brief pushBodies Push a new Body to the current List
     */
    void pushBodies(Body*);

    /**
     * @brief removeBody Remove a Body from the Universe
     * @return Returns True on success; otherwise returns False
     */
    bool removeBody(Body*);

    /**
     * @brief setBodies Replace all of the current Bodies with a new List
     */
    void setBodies(QList<Body*>);

    /**
     * @brief simulateStep Tick the simulation
     * @param deltaTime
     */
    void simulateStep(double deltaTime);

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

signals:
    /**
     * @brief stepFinished Signal emitted when simulateStep() completes
     */
    void stepFinished();

private:
    // List of all bodies in simulation
    QList<Body*> bodies;

    // Amount to accelerate time by
    double timeAcceleration;
};

#endif // UNIVERSE_H
