#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QGraphicsScene>
#include <QDebug>

#include <Vector>

#include "particle.h"
#include "renderbody.h"

struct ParticleFlags
{
    enum Value
    {
        RANDOMIZE_INITIAL_ROTATION = (1<<0)
    };
};

class ParticleEmitter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ParticleEmitter Create a new Particle Emitter
     * @param scene
     * @param flags
     * @param parent QObject. If it is a RenderBody, the ParticleEmitter will be attached to it.
     */
    explicit ParticleEmitter(QGraphicsScene* scene, ParticleFlags::Value flags, QObject *parent = 0);

    /**
     * @brief setOffset Set the offset to create the Particles releative to the RenderBody
     * @param offset
     */
    void setOffset(double offset);

    /**
     * @brief setScaleCurve Set the scale Bezier curve that will pass through the three given points.
     * @param p0
     * @param pc
     * @param p2
     */
    void setScaleCurve(double p0, double pc, double p2);

    /**
     * @brief setRedCurve Set the red color Bezier curve that will pass through p0, pc, and p2.
     * @param p0
     * @param pc
     * @param p2
     */
    void setRedCurve(double p0, double pc, double p2);

    /**
     * @brief setBlueCurve Set the blue color Bezier curve that will pass through p0, pc, and p2.
     * @param p0
     * @param pc
     * @param p2
     */
    void setBlueCurve(double p0, double pc, double p2);

    /**
     * @brief setGreenCurve Set the green color Bezier curve that will pass through p0, pc, and p2.
     * @param p0
     * @param pc
     * @param p2
     */
    void setGreenCurve(double p0, double pc, double p2);

    /**
     * @brief setParticleLife Set the Particle's life time in seconds
     * @param particleLife
     */
    void setParticleLife(double particleLife);

    /**
     * @brief setGenerationTime Set the amount of seconds between each particle generation.
     * @param generationTime
     */
    void setGenerationTime(double generationTime);

    /**
     * @brief setEnabled Enable or disable the creation of new Particles
     * @param enabled
     */
    void setEnabled(bool enabled);

signals:

public slots:
    /**
     * @brief tick Updates the Particles and creates new ones if enabled
     * @param deltaTime
     */
    void tick(double deltaTime);

private:
    /**
     * @brief getBezierCurve Calculate the center control point, and return it via curve
     * @param p0
     * @param pc
     * @param p2
     * @param curve
     */
    void getBezierCurve(double p0, double pc, double p2, double curve[]);

    /**
     * @brief getBezierPoint Calculate the Bezier curve point
     * @param t
     * @param curve
     * @return
     */
    double getBezierPoint(double t, double curve[]);

    /**
     * @brief clamp Clamp value to between min and max
     * @param value
     * @param min
     * @param max
     * @return
     */
    double clamp(double value, double min, double max);

    // Particles that are currently alive
    QList<Particle*> particles;

    // Bezier curves
    double scaleCurve[3];
    double redCurve[3];
    double blueCurve[3];
    double greenCurve[3];

    // Particle information
    double offset;
    Vector position;
    Vector velocity;
    double generationTime;
    double particleLife;
    bool enabled;

    // References to stuff ParticleEmitter needs
    QGraphicsScene* scene;
    RenderBody* body;

    // Keeping time between Particle generations
    double timeAccumulator;

    // Flags
    ParticleFlags::Value flags;
};

#endif // PARTICLESYSTEM_H
