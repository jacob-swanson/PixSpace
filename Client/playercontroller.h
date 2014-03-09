#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <RenderBody>
#include <Vector>
#include <QDebug>
#include "controller.h"

// Struct to store keybindings for the controller
struct keybinding
{
    int forward;
    int backward;
    int turnLeft;
    int turnRight;
};

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
    // Keybindings will be stored in here
    keybinding keybindings;

};

#endif // PLAYERCONTROLLER_H
