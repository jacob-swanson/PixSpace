#include "playercontroller.h"

PlayerController::PlayerController(QObject *parent) :
    Controller(parent)
{
    // TODO: Load keybindings from storage (DB or local file) so that they can be user configured
    this->keybindings.forward = Qt::Key_W;
    this->keybindings.backward = Qt::Key_S;
    this->keybindings.turnLeft = Qt::Key_A;
    this->keybindings.turnRight = Qt::Key_D;
}

void PlayerController::tick(double deltaTime)
{
    this->body->tick(deltaTime);
}

void PlayerController::possess(Body *body)
{
    this->body = dynamic_cast<RenderBody*>(body);
}

Body* PlayerController::getPossessed()
{
    return this->body;
}

void PlayerController::unPossess()
{
    this->body = NULL;
}

Vector PlayerController::getPosition()
{
    return this->body->getPosition();
}

void PlayerController::read(QJsonObject &json)
{
    this->body = new RenderBody();
    this->body->read(json["body"].toObject());
}

void PlayerController::write(QJsonObject &json)
{
    QJsonObject bodyObject;
    this->body->write(bodyObject);

    json["body"] = bodyObject;
    json["type"] = QString("PlayerController");
}

void PlayerController::handleKeyPress(int key)
{
    // TODO: Handle more than just movement
    // TDOO: Convert into calls to make ship move
    // A switch statement does not work as it seems to require constants, and keybindings will be loaded in later
    if (key == keybindings.forward)
    {
        emit thrustForward(true);
    }
    else if (key == keybindings.backward)
    {
        emit thrustReverse(true);
    }
    else if (key == keybindings.turnLeft)
    {
        emit rotateLeft(true);
    }
    else if (key == keybindings.turnRight)
    {
        emit rotateRight(true);
    }
}

void PlayerController::handleKeyRelease(int key)
{
    // TODO: Handle more than just movement
    // TDOO: Convert into calls to make ship stop moving
    // A switch statement does not work as it seems to require constants, and keybindings will be loaded in later
    if (key == keybindings.forward)
    {
        emit thrustForward(false);
    }
    else if (key == keybindings.backward)
    {
        emit thrustReverse(false);
    }
    else if (key == keybindings.turnLeft)
    {
        emit rotateLeft(false);
    }
    else if (key == keybindings.turnRight)
    {
        emit rotateRight(false);
    }
}
