#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>
#include <QSocketNotifier>
#include <QTimer>
#include <QElapsedTimer>
#include <QJsonDocument>

#include <unistd.h>
#include <sys/socket.h>

#include <Universe>

#include "networkserver.h"
#include "datamanager.h"

#include <QMainWindow>

namespace Ui {
class ServerApp;
}

class ServerApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerApp(QWidget *parent = 0);
    ~ServerApp();

signals:
    /**
     * @brief finished Emitted when simulation stops
     */
    void finished();

    /**
     * @brief endTick Emmited at the end of each tick
     */
    void endTick(int);

private slots:
    /**
     * @brief displayConnection Display the username of a new connection
     * @param connection
     */
    void displayConnection(Connection* connection);

    /**
     * @brief displayDisconnection Display the username of a connection that has disconnectes
     * @param username
     */
    void displayDisconnection(QString username);

    /**
     * @brief handleMessage Handle a message from a client
     * @param username
     * @param message
     */
    void receiveMessage(QString username, QString message);

    /**
     * @brief updateNewSpeedValue Updates UI to reflect the slider's current value
     * @param speed
     */
    void updateNewSpeedValue(int speed);

    /**
     * @brief updateTimeAcceleration Updates the universes time acceleration value to reflect the slider's position
     * @param speed
     */
    void updateTimeAcceleration(int speed);

    /**
     * @brief updateTimeAccelerationRequest Called when update button for time acceleration clicked
     */
    void updateTimeAccelerationRequest();

    /**
     * @brief updateSQLConfig Updates the server config file with new values for SQL stuff from the UI
     */
    void updateSQLConfig();


public slots:
    /**
     * @brief tick Tick the simulation
     */
    void tick();

    /**
     * @brief start Start ticking the simulation
     */
    void start();

    /**
     * @brief stop Stop ticking the application and emit finished()
     */
    void stop();

    /**
     * @brief broadcastBodies Broadcast the Universe to all
     */
    void broadcastBodies();

private:

    /**
     * @brief updateNewSpeedLabel Updates the speed label in the UI to the correct values
     * @param speed
     */
    void updateNewSpeedLabel(int speed);


    // Data structures
    Universe *universe;
    NetworkServer *server;

    // Timers
    QElapsedTimer timer;
    QTimer tickTimer;

    Ui::ServerApp *ui;
};

#endif // SERVERAPP_H
