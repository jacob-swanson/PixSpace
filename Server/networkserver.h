#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QTcpServer>
#include <QList>

#include <Connection>

class NetworkServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);

    /**
     * @brief broadcastMessage Send a message to all clients
     * @param message
     */
    void broadcastMessage(QString message);

signals:
    /**
     * @brief newConnection Emitted when a new Connection is received
     * @param connection
     */
    void newConnection(Connection *connection);

    /**
     * @brief disconnection Emitted when a Connection disconnects
     * @param username Username from the Connection
     */
    void disconnection(QString username);

protected:
    /**
     * @brief incomingConnection Convert socketDescriptor to a Connection, and emit newConnection with it
     * @param socketDescriptor
     */
    void incomingConnection(qintptr socketDescriptor);

private slots:
    /**
     * @brief clientDisconnected Remove a Connection from clients
     */
    void clientDisconnected();

private:
    // List of clients
    QList<Connection*> clients;
};

#endif // NETWORKSERVER_H
