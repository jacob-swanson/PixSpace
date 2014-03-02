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

signals:
    /**
     * @brief newConnection Emitted when a new Connection is received
     * @param connection
     */
    void newConnection(Connection *connection);

protected:
    /**
     * @brief incomingConnection Convert socketDescriptor to a Connection, and emit newConnection with it
     * @param socketDescriptor
     */
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<Connection*> clients;
};

#endif // NETWORKSERVER_H
