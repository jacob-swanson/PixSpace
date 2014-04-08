#include "clientgraphicsscene.h"

ClientGraphicsScene::ClientGraphicsScene() : QGraphicsScene()
{
    this->controllerMode = false;
}

void ClientGraphicsScene::setControllerMode(bool controllerMode)
{
    this->controllerMode = controllerMode;
}

void ClientGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    // If currently in controller mode then pass key events to the controller object
    if (controllerMode)
    {
        emit keyPressed(event->key());
    }
    // Otherwise we are handling some kind of "other" input like network setup, so pass up to QGraphicsScene to handle
    else
    {
        QGraphicsScene::keyPressEvent(event);
    }
}

void ClientGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    // If currently in controller mode then pass key events to the controller object
    if (controllerMode)
    {
        emit keyReleased(event->key());
    }
    // Otherwise we are handling some kind of "other" input like network setup, so pass up to QGraphicsScene to handle
    else
    {
        QGraphicsScene::keyReleaseEvent(event);
    }
}
