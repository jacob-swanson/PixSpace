#include "particleemitter.h"

ParticleEmitter::ParticleEmitter(QGraphicsScene* scene, ParticleFlags::Value flags, QObject *parent) :
    QObject(parent)
{
    this->scene = scene;
    this->flags = flags;

    this->getBezierCurve(0.3, 1.0, 0.0, this->scaleCurve);
    this->getBezierCurve(0.0, 1.0, 0.3, this->redCurve);
    this->getBezierCurve(0.0, 0.6, 0.3, this->greenCurve);
    this->getBezierCurve(0.0, 0.0, 1.0, this->blueCurve);

    this->position = Vector(0.0, 0.0);
    this->velocity = Vector(5.0, 5.0);
    this->particleLife = 20.0;

    this->generationTime = 2.0;
}

void ParticleEmitter::getBezierCurve(double p0, double pc, double p2, double curve[])
{
    // Calculate a value for p1 that will make the curve pass through pc
    double p1 = (2 * pc) - (0.5 * p0) - (0.5 * p2);
    curve[0] = p0;
    curve[1] = p1;
    curve[2] = p2;
}

double ParticleEmitter::getBezierPoint(double t, double curve[])
{
    return (curve[0]*(t*t))
            + (curve[1]*2*t*(1-t))
            + (curve[2]*(1-t)*(1-t));
}

void ParticleEmitter::tick(double deltaTime)
{
    this->timeAccumulator += deltaTime;

    if (this->timeAccumulator > this->generationTime)
    {
        // Generate a particle
        Particle* particle = new Particle(this->scene, ":/bodies/Particle");
        particle->addPosition(this->position);
        if (this->flags & ParticleFlags::RANDOMIZE_INITIAL_ROTATION)
        {
            particle->setRotation(rand() % 360);
        }
        this->particles.push_back(particle);

        this->timeAccumulator = 0.0;
    }

    // Update particles
    foreach (Particle* particle, this->particles)
    {
        // Update position
        particle->addPosition(this->velocity * deltaTime);

        // Apply scale curve
        double percentLife = particle->getLife() / this->particleLife;
        particle->setScale(this->getBezierPoint(percentLife, this->scaleCurve));

        // Apply color curve
        QColor color;
        color.setRed(this->clamp(this->getBezierPoint(percentLife, this->redCurve) * 255, 0.0, 255));
        color.setBlue(this->clamp(this->getBezierPoint(percentLife, this->blueCurve) * 255, 0.0, 255));
        color.setGreen(this->clamp(this->getBezierPoint(percentLife, this->greenCurve) * 255, 0.0, 255));
        particle->setColor(color);

        // If the particle has lived long enough, remove it
        if (particle->addLife(deltaTime) > this->particleLife)
        {
            particle->remove();
            this->particles.removeOne(particle);
            particle->deleteLater();
        }
    }
}

double ParticleEmitter::clamp(double value, double min, double max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}


