#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QTcpServer>

#include "connection.h"

class NetworkServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);

signals:
    void newConnection(Connection *connection);

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // NETWORKSERVER_H
