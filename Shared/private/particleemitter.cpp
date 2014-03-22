#include <qmath.h>
#include "particleemitter.h"

#define PI 3.14159265

ParticleEmitter::ParticleEmitter(QGraphicsScene* scene, ParticleFlags::Value flags, QObject *parent) :
    QObject(parent)
{
    RenderBody* body = dynamic_cast<RenderBody*>(parent);
    if (body != NULL)
    {
        this->body = body;
    }
    this->scene = scene;
    this->flags = flags;

    // Default values
    this->particleLife = 20.0;
    this->generationTime = 2.0;
}

void ParticleEmitter::setScaleCurve(double p0, double pc, double p2)
{
    this->getBezierCurve(p0, pc, p2, this->scaleCurve);
}

void ParticleEmitter::setRedCurve(double p0, double pc, double p2)
{
    this->getBezierCurve(p0, pc, p2, this->redCurve);
}

void ParticleEmitter::setBlueCurve(double p0, double pc, double p2)
{
    this->getBezierCurve(p0, pc, p2, this->blueCurve);
}

void ParticleEmitter::setGreenCurve(double p0, double pc, double p2)
{
    this->getBezierCurve(p0, pc, p2, this->greenCurve);
}

void ParticleEmitter::setParticleLife(double particleLife)
{
    this->particleLife = particleLife;
}

void ParticleEmitter::setGenerationTime(double generationTime)
{
    this->generationTime = generationTime;
}

void ParticleEmitter::setEnabled(bool enabled)
{
    this->enabled = enabled;
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

    // Generate a particle every generationTime
    if (this->timeAccumulator > this->generationTime)
    {
        if (this->enabled)
        {
            // Generate a particle at a set location, or at the location of the target body
            Particle* particle = new Particle(this->scene, ":/bodies/Particle");
            if (this->body != NULL)
            {
                Vector dir;
                dir.setY(qCos(this->body->getRotation() * PI / 180));
                dir.setX(-1*qSin(this->body->getRotation() * PI / 180));
                dir = dir * this->offset;
                particle->addPosition(this->body->getScreenPosition() + dir);
            }
            else
            {
                particle->addPosition(this->position);
            }

            // Randomize the initial rotation
            if (this->flags & ParticleFlags::RANDOMIZE_INITIAL_ROTATION)
            {
                particle->setRotation(rand() % 360);
            }

            // Keep track of the particle
            this->particles.push_back(particle);
        }

        this->timeAccumulator = 0.0;
    }

    // Update particles
    foreach (Particle* particle, this->particles)
    {
        // Update position
        particle->addPosition(this->velocity * deltaTime);

        // Apply scale curve
        double percentLife = particle->getLife() / this->particleLife;
        particle->setScale(clamp(this->getBezierPoint(percentLife, this->scaleCurve), 0.0, 1.0));

        // Apply color curve
        QColor color;
        color.setRed(static_cast<uint>(this->clamp(this->getBezierPoint(percentLife, this->redCurve) * 255, 0.0, 255)));
        color.setBlue(static_cast<uint>(this->clamp(this->getBezierPoint(percentLife, this->blueCurve) * 255, 0.0, 255)));
        color.setGreen(static_cast<uint>(this->clamp(this->getBezierPoint(percentLife, this->greenCurve) * 255, 0.0, 255)));
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
    if (value <= min)
    {
        return min;
    }
    else if (value >= max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

void ParticleEmitter::setOffset(double offset)
{
    this->offset = offset;
}



