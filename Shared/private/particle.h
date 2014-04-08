#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include <cstdlib>

#include <Vector>

class Particle : public QObject
{
    Q_OBJECT
public:
    explicit Particle(QGraphicsScene *scene, QString resource, QObject *parent = 0);

    /**
     * @brief addPosition Add a delta to the Particle's position
     * @param position
     */
    void addPosition(Vector position);

    /**
     * @brief addLife Add deltaTime to Particle's life, and return the new value
     * @param deltaTime
     * @return
     */
    double addLife(double deltaTime);

    /**
     * @brief getLife Get number of seconds the particle has been alive
     * @return
     */
    double getLife();

    /**
     * @brief remove Remove the Particle from the scene
     */
    void remove();

    /**
     * @brief setScale Set the graphicial scale of the Particle
     * @param scale
     */
    void setScale(double scale);

    /**
     * @brief setColor Set the color of the Particle
     * @param color
     */
    void setColor(QColor color);

    /**
     * @brief setRotation Set the rotation of the Particle
     * @param rotation
     */
    void setRotation(double rotation);

private:
    Vector position;
    double life;

    QPixmap* map;
    QGraphicsPixmapItem* graphicsItem;
    QGraphicsScene* scene;
};

#endif // PARTICLE_H
