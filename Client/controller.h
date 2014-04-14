#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>

#include <Ship>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    /**
     * @brief tick Tick the Controller
     * @param deltaTime
     */
    virtual void tick(double deltaTime) = 0;

    /**
     * @brief posssess Take control of a Body
     * @param body
     */
    virtual void possess(Ship* body) = 0;
};

#endif // CONTROLLER_H
