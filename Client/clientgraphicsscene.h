#ifndef CLIENTGRAPHICSSCENE_H
#define CLIENTGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>

class ClientGraphicsScene : public QGraphicsScene
{
    // QObject macro to allow this object to be a QObect (and thus emit a signal)
    Q_OBJECT

public:
    ClientGraphicsScene();
    /**
     * @brief setControllerMode Sets input to be passed to controller (true) or to be passed up to QGraphicsScene (false)
     * @param controllerMode bool
     */
    void setControllerMode(bool controllerMode);

private:
    /**
     * @brief keyPressEvent Executed when a keypress event happens
     * @param event Key press event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief controllerMode Indicates whether to pass input to controller or parent
     */
    bool controllerMode;

signals:
    /**
     * @brief key Pressed Emitted when a key is pressed inside the graphics scene
     * @param key Value of the key pressed
     */
    void keyPressed(int key);
};

#endif // CLIENTGRAPHICSSCENE_H
