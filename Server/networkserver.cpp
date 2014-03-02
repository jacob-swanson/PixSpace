#include "networkserver.h"

NetworkServer::NetworkServer(QObject *parent) :
    QTcpServer(parent)
{
}

void NetworkServer::incomingConnection(qintptr socketDescriptor)
{
    // Convert socketDescriptor to Connection
    Connection *connection = new Connection("Server", this);
    connection->setSocketDescriptor(socketDescriptor);

    connect(connection, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError()));
    emit newConnection(connection);
}

void NetworkServer::clientDisconnected()
{
    // Get the connection
    Connection *connection = qobject_cast<Connection*>(sender());

    // Remove it from the list
    this->clients.removeOne(connection);

    // Emit a signal for the disconnection
    QString username = connection->getName();
    emit disconnection(username);

    // Delete the object
    connection->deleteLater();
}

void NetworkServer::broadcastMessage(QString message)
{
    // Send message to all clients
    foreach (Connection* connection, this->clients)
    {
        connection->sendMessage(message);
    }
}

void NetworkServer::displayError()
{
    Connection *connection = qobject_cast<Connection*>(sender());

    qDebug() << "The following error occured: " << connection->errorString();
}

