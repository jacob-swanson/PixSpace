#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QGraphicsScene>
#include <QDebug>

#include <Vector>

#include "particle.h"

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
    explicit ParticleEmitter(QGraphicsScene* scene, ParticleFlags::Value flags, QObject *parent = 0);

    void getBezierCurve(double p0, double pc, double p2, double curve[]);

    double getBezierPoint(double t, double curve[]);

signals:

public slots:
    void tick(double deltaTime);

private:
    double clamp(double value, double min, double max);
    QList<Particle*> particles;

    double scaleCurve[3];
    double redCurve[3];
    double blueCurve[3];
    double greenCurve[3];

    Vector position;
    Vector velocity;
    double generationTime;
    double particleLife;

    QGraphicsScene* scene;

    double timeAccumulator;

    ParticleFlags::Value flags;
};

#endif // PARTICLESYSTEM_H
