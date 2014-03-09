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

    this->universe = new Universe();

    this->tickTimer.setInterval(15);
    this->controller = new PlayerController();

    connect(&this->tickTimer, SIGNAL(timeout()), this, SLOT(tickSimulation()));
    connect(this, SIGNAL(tickFinished()), this, SLOT(sendClientBody()));
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
    connect(this->connection, SIGNAL(newMessage(QString,QString)), this, SLOT(receiveMessage(QString,QString)));
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
    this->tickTimer.start();

    Ship* b = new Ship("FireflyShip", this->connection->getGreetingMessage());
    b->setPosition(-2.0e8, -2.0e8);
    this->controller->possess(b);
    this->universe->pushBodies(b);
}

void ClientApp::displayConnectionError()
{
    qDebug() << "Connection error: " << this->connection->errorString();

    // Destory the connection
    this->connection->disconnectFromHost();
    this->connection->deleteLater();

    // Show the connection dialog
    delete this->universe;
    this->universe = new Universe();
    this->scene->clear();
    this->showConnectionDialog();
}

void ClientApp::showConnectionDialog()
{
    // Setup the server connection dialog
    ConnectionDialog* dialog = new ConnectionDialog();
    QGraphicsProxyWidget* item = this->scene->addWidget(dialog, Qt::Dialog | Qt::WindowTitleHint);

    connect(dialog, SIGNAL(connectToServer(QString,int,QString)),
            this, SLOT(connectToServer(QString,int,QString)));
    connect(dialog, SIGNAL(quit()), this, SLOT(exitClient()));
}

void ClientApp::receiveMessage(QString username, QString message)
{
    QJsonDocument universeDocument = QJsonDocument::fromJson(message.toLocal8Bit());

    // Assuming the the message will be Universe JSON
    this->universe->read(universeDocument.object());
}

void ClientApp::tickSimulation()
{
    foreach(Body* b, this->universe->getBodies())
    {
        RenderBody* rb = dynamic_cast<RenderBody*>(b);
        if (rb != NULL)
        {
            QGraphicsPixmapItem* item = NULL;
            item = rb->getGraphicsItem();

            // Update the graphical component
            if (item == NULL)
            {
                if (rb->createGraphic())
                {
                    item = rb->getGraphicsItem();
                    item->setPos(this->getPixelFromSimulation(b->getPosition().getX()), this->getPixelFromSimulation(b->getPosition().getY()));
                    this->scene->addItem(item);
                }
            }
            else
            {
                item->setPos(this->getPixelFromSimulation(b->getPosition().getX()), this->getPixelFromSimulation(b->getPosition().getY()));
            }
        }
    }

    emit tickFinished();
}

int ClientApp::getPixelFromSimulation(const double value) const
{
    double newValue = value / 1000000.0;
    double roundedValue = round(newValue);

    return (int)roundedValue;
}

void ClientApp::sendClientBody()
{
    QJsonObject universeObject;
    this->universe->write(universeObject);

    QJsonDocument jsonDocument(universeObject);
    this->connection->sendMessage(jsonDocument.toJson());
}
