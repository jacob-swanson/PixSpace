#include "playercontroller.h"

PlayerController::PlayerController(QObject *parent) :
    Controller(parent)
{
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

}
