#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <RenderBody>
#include <Vector>
#include <QDebug>
#include <QMessageBox>

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
    Body* getPossessed();
    void unPossess();
    Vector getPosition();
    void read(QJsonObject &json);
    void write(QJsonObject &json);


public slots:
    /**
     * @brief handleKeyPress Handles input when a key is pressed by the player
     * @param key Int value of the key pressed
     */
    void handleKeyPress(int key);
    /**
     * @brief handleKeyRelease Handles input when a key is released by the player
     * @param key Int value of the key released
     */
    void handleKeyRelease(int key);

private:
    RenderBody* body;
    keybinding keybindings;

    // Rotation/Thrust flags
    bool rotRight;
    bool rotLeft;
    bool thrustForward;
    bool thrustBackward;

 signals:
    // Signal to quit application
    void exit();
    // Signal to return to the server connection dialog
    void returnMenu();
};

#endif // PLAYERCONTROLLER_H
