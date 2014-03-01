#include "networkserver.h"

NetworkServer::NetworkServer(QObject *parent) :
    QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void NetworkServer::incomingConnection(qintptr socketDescriptor)
{
    Connection * connection = new Connection(this);
    connection->setSocketDescriptor(socketDescriptor);
    emit newConnection(connection);
}
