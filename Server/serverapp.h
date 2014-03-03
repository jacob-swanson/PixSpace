#ifndef APP_H
#define APP_H

#include <QObject>
#include <QSocketNotifier>
#include <QTimer>
#include <QElapsedTimer>

#include <unistd.h>
#include <sys/socket.h>

#include <Universe>
#include <DataManager>

#include "networkserver.h"

class ServerApp : public QObject
{
    Q_OBJECT
public:
    explicit ServerApp(QObject *parent = 0);

    // Unix signal handlers, called by system.
    static void hupSignalHandler(int unused);
    static void termSignalHandler(int unused);
    static void intSignalHandler(int unused);

signals:
    /**
     * @brief finished Emitted when simulation stops
     */
    void finished();

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
     * @brief handleSigHup Called when SIGHUP occurs
     */
    void handleSigHup();

    /**
     * @brief handleSigTerm Called when SIGTERM occurs
     */
    void handleSigTerm();

    /**
     * @brief handleSigInt Called when SIGINT occurs
     */
    void handleSigInt();

private:
    // Sockets
    static int sighupFd[2];
    static int sigtermFd[2];
    static int sigintFd[2];

    QSocketNotifier *snHup;
    QSocketNotifier *snTerm;
    QSocketNotifier *snInt;

    // Data structures
    Universe *universe;
    DataManager *datamanager;
    NetworkServer *server;

    // Timers
    QElapsedTimer timer;
    QTimer tickTimer;
};

#endif // APP_H
