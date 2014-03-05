#include "clientapp.h"

ClientApp::ClientApp(QObject *parent) :
    QObject(parent)
{
    // Setup the GraphicsView and GraphicsScene
    this->view = new QGraphicsView();
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->scene = new QGraphicsScene();
    view->setScene(this->scene);

    this->showConnectionDialog();

//    RenderBody body2;
//    body2.loadImageByteArray("a");
//    body2.createGraphic();
//    body2.getGraphicsItem()->setPos(100, 100);
//    space.addItem(body2.getGraphicsItem());
//    view.centerOn(body2.getGraphicsItem());
}

void ClientApp::connectToServer(QString address, int port, QString name)
{
    // Connect to a server
    qDebug() << "Address: " << address;
    qDebug() << "Port: " << port;
    qDebug() << "Name: " << name;

    this->connection = new Connection(name, this);
    this->connection->connectToHost(address, port);

    connect(this->connection, SIGNAL(readyForUse()), this, SLOT(connectionSuccessful()));
    connect(this->connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayConnectionError()));
}

void ClientApp::show()
{
    // Show the client
    this->view->show();
}

void ClientApp::exitClient()
{
    // Exit the application
    QCoreApplication::quit();
}

void ClientApp::connectionSuccessful()
{
    // Clear out the scene to prepair for the game loading
    this->scene->clear();
}

void ClientApp::displayConnectionError()
{
    qDebug() << "Connection error: " << this->connection->errorString();

    // Destory the connection
    this->connection->disconnectFromHost();
    this->connection->deleteLater();

    // Show the connection dialog
    this->scene->clear();
    this->showConnectionDialog();
}

void ClientApp::showConnectionDialog()
{
    // Setup the server connection dialog
    ConnectionDialog* dialog = new ConnectionDialog();
    this->scene->addWidget(dialog, Qt::Dialog | Qt::WindowTitleHint);

    connect(dialog, SIGNAL(connectToServer(QString,int,QString)),
            this, SLOT(connectToServer(QString,int,QString)));
    connect(dialog, SIGNAL(quit()), this, SLOT(exitClient()));
}
