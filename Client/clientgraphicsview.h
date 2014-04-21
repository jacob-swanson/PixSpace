#ifndef CLIENTGRAPHICSVIEW_H
#define CLIENTGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#include "playercontroller.h"

class ClientGraphicsView : public QGraphicsView
{
public:
    /**
     * @brief ClientGraphicsView
     * @param parent
     */
    explicit ClientGraphicsView(QObject *parent = 0);

    /**
     * @brief setController Set the controller, so the view can draw the HUD
     * @param controller
     */
    void setController(PlayerController* controller);

protected:
    /**
     * @brief wheelEvent Zooming
     * @param event
     */
    virtual void wheelEvent(QWheelEvent *event);

    /**
     * @brief paintEvent Paint the HUD
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event);

private:
    PlayerController* controller;
};

#endif // CLIENTGRAPHICSVIEW_H
