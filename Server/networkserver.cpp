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
    connect(connection, SIGNAL(newMessage(QString,QString)), this, SLOT(receiveMessage(QString,QString)));
    connect(connection, SIGNAL(readyForUse()), this, SLOT(clientConnected()));
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

void NetworkServer::clientConnected()
{
    Connection *connection = qobject_cast<Connection*>(sender());

    // Check if there is already a user connected
    foreach (Connection* existingConnection, this->clients)
    {
        // If user is in the list, abort the new connection
        if (existingConnection->getName() == connection->getName())
        {
            connection->abort();
            return;
        }
    }

    // Assuming everything went well (i.e. return didn't get called) add the connection to the list
    this->clients.push_back(connection);

    emit newConnection(connection);
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

void NetworkServer::broadcastJson(QByteArray message)
{
    foreach (Connection* connection, this->clients)
    {
        connection->sendMessage(QString(message));
    }
}

void NetworkServer::receiveMessage(QString username, QString message)
{
    emit newMessage(username, message);
}

QString NetworkServer::getConnectedUsers()
{
    QString connectedUsers = "";
    foreach (Connection* existingConnection, this->clients)
    {
        connectedUsers = connectedUsers + existingConnection->getName() + "\n";
    }

    return connectedUsers;
}
