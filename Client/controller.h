#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>

#include <Body>

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
    virtual void possess(Body* body) = 0;

    /**
     * @brief unPossess Release control of a Body
     */
    virtual void unPossess() = 0;

    /**
     * @brief getPosition Get the position of the controller
     */
    virtual Vector getPosition() = 0;

    /**
     * @brief read Read in the Controller from JSON
     * @param json
     */
    virtual void read(QJsonObject &json) = 0;

    /**
     * @brief write Write out the controller to JSON
     * @param json
     */
    virtual void write(QJsonObject &json) = 0;

};

#endif // CONTROLLER_H
