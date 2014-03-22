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

    void addPosition(Vector position);

    /**
     * @brief addLife Add deltaTime to Particle's life, and return the new value
     * @param deltaTime
     * @return
     */
    double addLife(double deltaTime);

    double getLife();

    void remove();

    void setScale(double scale);

    void setColor(QColor color);

    void setRotation(double rotation);

private:
    Vector position;
    double life;

    QPixmap* map;
    QGraphicsPixmapItem* graphicsItem;
    QGraphicsScene* scene;
};

#endif // PARTICLE_H
