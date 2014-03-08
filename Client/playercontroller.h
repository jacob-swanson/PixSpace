#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <RenderBody>
#include <Vector>

#include "controller.h"

class PlayerController : public Controller
{
    Q_OBJECT
public:
    explicit PlayerController(QObject *parent = 0);

    void tick(double deltaTime);
    void possess(Body *body);
    void unPossess();
    Vector getPosition();
    void read(QJsonObject &json);
    void write(QJsonObject &json);

public slots:
    void handleKeyPress(int key);

private:
    RenderBody* body;

};

#endif // PLAYERCONTROLLER_H
