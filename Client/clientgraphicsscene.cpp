#include "clientgraphicsscene.h"

ClientGraphicsScene::ClientGraphicsScene()
{
}

void ClientGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event->key());
    QGraphicsScene::keyPressEvent(event);
}
