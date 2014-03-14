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

    /**
     * @brief broadcastJson Broadcast a QByteArray, it is expected to be JSON
     * @param message
     */
    void broadcastJson(QByteArray message);

    /**
     * @brief getConnectedUsers Returns a string of connected users separated by \n
     * @return QString
     */
    QString getConnectedUsers();

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

    /**
     * @brief newMessage Emitted when a new message is received from a Connection
     * @param username
     * @param message
     */
    void newMessage(QString username, QString message);

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

    /**
     * @brief clientConnected
     */
    void clientConnected();

    /**
     * @brief displayError Print out a socket error
     */
    void displayError();

    /**
     * @brief receiveMessage Relay a message from a connected Connection
     * @param username
     * @param message
     */
    void receiveMessage(QString username, QString message);

private:    
    // List of clients
    QList<Connection*> clients;
};

#endif // NETWORKSERVER_H
