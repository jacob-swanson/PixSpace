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

private:
    /**
     * @brief keyPressEvent Executed when a keypress event happens
     * @param event Key press event
     */
    void keyPressEvent(QKeyEvent *event);

signals:
    /**
     * @brief key Pressed Emitted when a key is pressed inside the graphics scene
     * @param key Value of the key pressed
     */
    void keyPressed(int key);
};

#endif // CLIENTGRAPHICSSCENE_H
