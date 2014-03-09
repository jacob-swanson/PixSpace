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

}

void PlayerController::possess(Body *body)
{
    this->body = dynamic_cast<RenderBody*>(body);
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
        qDebug() << "Move ship forward";
    }
    else if (key == keybindings.backward)
    {
        qDebug() << "Move ship backward";
    }
    else if (key == keybindings.turnLeft)
    {
        qDebug() << "Turn ship left.";
    }
    else if (key == keybindings.turnRight)
    {
        qDebug() << "Turn ship right.";
    }
}

void PlayerController::handleKeyRelease(int key)
{
    // TODO: Handle more than just movement
    // TDOO: Convert into calls to make ship stop moving
    // A switch statement does not work as it seems to require constants, and keybindings will be loaded in later
    if (key == keybindings.forward)
    {
        qDebug() << "Stop moving ship forward";
    }
    else if (key == keybindings.backward)
    {
        qDebug() << "Stop moving ship backward";
    }
    else if (key == keybindings.turnLeft)
    {
        qDebug() << "Stop turning ship left.";
    }
    else if (key == keybindings.turnRight)
    {
        qDebug() << "Stop turning ship right.";
    }
}
