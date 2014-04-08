#include "playercontroller.h"

PlayerController::PlayerController(Universe* universe, QObject *parent) :
    Controller(parent)
{
    // TODO: Load keybindings from storage (DB or local file) so that they can be user configured
    this->keybindings.forward = Qt::Key_W;
    this->keybindings.backward = Qt::Key_S;
    this->keybindings.turnLeft = Qt::Key_A;
    this->keybindings.turnRight = Qt::Key_D;
    this->keybindings.center = Qt::Key_C;

    this->universe = universe;

    this->rotRight = false;
    this->rotLeft = false;
    this->thrustForward = false;
    this->thrustBackward = false;
}

void PlayerController::setUniverse(Universe* universe)
{
    this->universe = universe;
}

void PlayerController::tick(double deltaTime)
{
    if (rotLeft)
    {
        double rotation = this->body->getRotation();
        this->body->setRotation(rotation - (this->body->getRotationRate() * deltaTime));
    }

    if (rotRight)
    {
        double rotation = this->body->getRotation();
        this->body->setRotation(rotation + (this->body->getRotationRate() * deltaTime));
    }

    if (thrustForward)
    {
        this->body->increaseThrottle(deltaTime);
    }

    if (thrustBackward)
    {
        this->body->decreaseThrottle(deltaTime);
    }

    this->body->calculateForces(this->universe->getBodies(), this->universe->getTimeAcceleration(), deltaTime);
    this->body->tick(deltaTime);
}

void PlayerController::possess(Ship *body)
{
    this->body = body;
}

Ship* PlayerController::getPossessed()
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
    this->body = new Ship();
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
        this->thrustForward = true;
    }
    else if (key == keybindings.backward)
    {
        this->thrustBackward = true;
    }
    else if (key == keybindings.turnLeft)
    {
        this->rotLeft = true;
    }
    else if (key == keybindings.turnRight)
    {
        this->rotRight = true;
    }
    // Escape key handling, launches dialog to quit. Not rebindable
    else if (key == Qt::Key_Escape)
    {
        QMessageBox quitBox;
        quitBox.setText("Do you really want to quit?");
        QPushButton *quitButton = quitBox.addButton("Quit to Desktop", QMessageBox::DestructiveRole);
        QPushButton *resume = quitBox.addButton("Return to Pixspace", QMessageBox::RejectRole);
        quitBox.exec();

        // If user selects exiting
        if (quitBox.clickedButton() == (QAbstractButton*) quitButton)
        {
            emit exit();
        }
        // All other cases should just resume the game

    }
    // Handles centering when the key for centering is pressed
    else if (key == keybindings.center)
    {
        emit center();
    }
}

void PlayerController::handleKeyRelease(int key)
{
    // TODO: Handle more than just movement
    // TDOO: Convert into calls to make ship stop moving
    // A switch statement does not work as it seems to require constants, and keybindings will be loaded in later
    if (key == keybindings.forward)
    {
        this->thrustForward = false;
    }
    else if (key == keybindings.backward)
    {
        this->thrustBackward = false;
    }
    else if (key == keybindings.turnLeft)
    {
        this->rotLeft = false;
    }
    else if (key == keybindings.turnRight)
    {
        this->rotRight = false;
    }
}
