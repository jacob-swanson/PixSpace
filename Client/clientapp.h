#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <cmath>

#include <QObject>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QElapsedTimer>

#include <RenderBody>
#include <Connection>
#include <Universe>
#include <Ship>

#include "connectiondialog.h"
#include "playercontroller.h"
#include "clientgraphicsscene.h"

class ClientApp : public QObject
{
    Q_OBJECT
public:
    explicit ClientApp(QObject *parent = 0);

signals:

public slots:
    /**
     * @brief show Display the Game
     */
    void show();

private slots:
    /**
     * @brief connectToServer Connect to the given server
     * @param address
     * @param port
     * @param name
     */
    void connectToServer(QString address, int port, QString name);

    /**
     * @brief exitClient Exit the application
     */
    void exitClient();

    /**
     * @brief connectionSuccessful The connection to the server was successful
     */
    void connectionSuccessful();

    /**
     * @brief displayConnectionError Print out a connection error, destroy the connection, and open the connection dialog
     */
    void displayConnectionError();

    /**
     * @brief showConnectionDialog Show the connection dialog
     */
    void showConnectionDialog();

    /**
     * @brief receiveMessage Handle a message from the Connection
     * @param username
     * @param message
     */
    void receiveMessage(QString username, QString message);

    /**
     * @brief tickSimulation Update the client side simulation
     */
    void tickSimulation();

    /**
     * @brief sendBodies Send client bodies to server.
     */
    void sendClientBody();

    /**
     * @brief bodyNotFound Handles the case when a body is not in the received Universe
     * Will add back the player's ship because it will be removed.
     * @param body
     */
    void bodyNotFound(Body* body);

    /**
     * @brief Disconnect Disconnects from the server and returns to server dialog
     */
    void Disconnect();

signals:
    /**
     * @brief tickFinished Emitted when a Simulation tick is finished
     */
    void tickFinished();

private:

    /**
     * @brief getPixelFromSimulation Scale down the value from the simulation to fit on a screen
     * @param value Value to scale down
     * @return
     */
    int getPixelFromSimulation(const double value) const;

    QGraphicsView* view;
    ClientGraphicsScene* scene;
    Connection* connection;

    Universe* universe;

    QTimer tickTimer;

    PlayerController* controller;

    QElapsedTimer timer;
};

#endif // CLIENTAPP_H
