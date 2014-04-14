#include "clientapp.h"
#include <QDebug>

ClientApp::ClientApp(QObject *parent) :
    QObject(parent)
{
    // Setup the GraphicsView and GraphicsScene
    this->view = new ClientGraphicsView();
    this->view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    this->scene = new ClientGraphicsScene;
    this->view->setScene(this->scene);

    this->connection = NULL;
    this->showConnectionDialog();

    this->universe = new Universe();
    connect(this->universe, SIGNAL(bodyNotFound(Body*)), this, SLOT(bodyNotFound(Body*)));

    this->tickTimer.setInterval(15);
    this->timer.start();
    this->controller = new PlayerController(this->universe);

    // Connect the keypress signal to the controller's keypress handler
    connect(this->scene, SIGNAL(keyPressed(int)), this->controller, SLOT(handleKeyPress(int)));
    // Connect the key release signal to the controller's key release handler
    connect(this->scene, SIGNAL(keyReleased(int)), this->controller, SLOT(handleKeyRelease(int)));

    // Connect the center signal to the center function
    connect(this->controller, SIGNAL(center()), this, SLOT(Center()));

    // Connect the quit signal in the player controller to quitting the application
    connect(this->controller, SIGNAL(exit()), this, SLOT(exitClient()));

    connect(&this->tickTimer, SIGNAL(timeout()), this, SLOT(tickSimulation()));
    connect(this, SIGNAL(tickFinished()), this, SLOT(sendClientBody()));
}

void ClientApp::bodyNotFound(Body *body)
{
    // If the body isn't the one we're controlling, remove its graphics item
    if (body->getId() != this->controller->getPossessed()->getId())
    {
        RenderBody* b = dynamic_cast<RenderBody*>(body);
        if (b != NULL)
        {
            this->scene->removeItem(b->getGraphicsItem());
            b->scheduleDelete();
        }
    }
    else
    {
        // The ship will be removed from the universe, so we need to add it back
        this->universe->pushBodies(body);
    }
}

void ClientApp::connectToServer(QString address, int port, QString name, QString shipName, QColor primColor, QColor secColor, QColor tertColor)
{
    // Connect to a server
    this->connection = new Connection(name, this);
    this->connection->connectToHost(address, port);
    this->shipName = shipName;
    this->primColor = primColor;
    this->secColor = secColor;
    this->tertColor = tertColor;

    connect(this->connection, SIGNAL(readyForUse()), this, SLOT(connectionSuccessful()));
    connect(this->connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayConnectionError()));
    connect(this->connection, SIGNAL(newMessage(QString,QString)), this, SLOT(receiveMessage(QString,QString)));
}

void ClientApp::show()
{
    // Show the client
    this->view->showMaximized();
}

void ClientApp::exitClient()
{
    // Destroy the connection before quitting
    if (this->connection != NULL)
    {
        this->connection->disconnectFromHost();
    }

    // Exit the application
    QCoreApplication::quit();
}

void ClientApp::connectionSuccessful()
{
    // Clear out the scene to prepair for the game loading
    // TODO: Remove ConnectionDialog from memory
    this->scene->clear();
    this->tickTimer.start();

    Ship* b = new Ship(this->shipName, this->connection->getGreetingMessage());
    b->setPosition(4.2e7, 0.0);
    b->setVelocity(0.0, 1e3);
    b->setRotationRate(50);
    b->setMass(10.8e2);
    b->setMaxThrust(1e3);
    b->setDiameter(1e7);
    b->setMasks(this->primColor.red(), this->primColor.green(), this->primColor.blue(), this->secColor.red(), this->secColor.green(), this->secColor.blue(), this->tertColor.red(), this->tertColor.green(), this->tertColor.blue());

    this->controller->possess(b);
    this->universe->pushBodies(b);
    this->view->setController(this->controller);
    connect(b, SIGNAL(collisionOccured(Body*)), this, SLOT(respawnShip()));

    // Swap the custom graphics scene keypress event handling to controller mode (keys control ship movement and actions rather than input to connection dialog)
    this->scene->setControllerMode(true);
}

void ClientApp::respawnShip()
{
    this->controller->getPossessed()->setPosition(4.2e7, 0.0);
    this->controller->getPossessed()->setVelocity(0.0, 1e3);
    this->controller->getPossessed()->setAcceleration(Vector(0.0, 0.0));
    this->controller->getPossessed()->setThrottle(0.0);
}

void ClientApp::displayConnectionError()
{
    QMessageBox errorBox;
    errorBox.setText("Connection error: " + this->connection->errorString());
    errorBox.exec();
}

void ClientApp::showConnectionDialog()
{
    // Setup the server connection dialog
    ConnectionDialog* dialog = new ConnectionDialog();
    dialog->setModal(true);
    dialog->show();

    connect(dialog, SIGNAL(connectToServer(QString,int,QString, QString, QColor, QColor, QColor)),
            this, SLOT(connectToServer(QString,int,QString, QString, QColor, QColor, QColor)));
    connect(dialog, SIGNAL(quit()), this, SLOT(exitClient()));
}

void ClientApp::receiveMessage(QString username, QString message)
{
    QJsonParseError error;
    QJsonDocument universeDocument = QJsonDocument::fromJson(message.toLocal8Bit(), &error);

    // Assuming the the message will be Universe JSON
    if (!error.error)
    {
        this->universe->read(universeDocument.object(), this->connection->getGreetingMessage());
    }
    else
    {
        // Non-fatal error, left as qDebug in case needed in the future, but definitely shouldn't grab at user's attention
        qDebug() << "Error parsing JSON: " << error.errorString();
    }
}

void ClientApp::tickSimulation()
{
    double deltaTime = ((double)this->timer.restart()/1000.0);
    if (deltaTime )

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
                if (rb->createGraphic(this->scene))
                {
                    item = rb->getGraphicsItem();
                    double scale = ((double)rb->getDiameter() / 100000.0)/ (double)item->boundingRect().width();
                    item->setScale(scale);
                    item->setPos(this->getPixelFromSimulation(b->getPosition().getX()), -1*this->getPixelFromSimulation(b->getPosition().getY()));
                    item->setRotation(rb->getRotation());
                    this->scene->addItem(item);
                }
                else
                {
                    QMessageBox errorBox;
                    errorBox.setText("A fatal error has occurred. Pixspace will now exit.");
                    errorBox.exec();
                    emit exitClient();
                }
            }
            else
            {
                item->setPos(this->getPixelFromSimulation(b->getPosition().getX()), -1*this->getPixelFromSimulation(b->getPosition().getY()));
                item->setRotation(rb->getRotation());
            }
        }

        rb->tick(deltaTime);
    }

    this->controller->tick(deltaTime);

    emit tickFinished();
}

int ClientApp::getPixelFromSimulation(const double value) const
{
    double newValue = value / 100000.0;
    double roundedValue = round(newValue);

    return (int)roundedValue;
}

void ClientApp::sendClientBody()
{
    QJsonObject shipObject;
    this->controller->getPossessed()->write(shipObject);

    QJsonDocument jsonDocument(shipObject);
    this->connection->sendMessage(jsonDocument.toJson());
}

void ClientApp::Center()
{
    this->view->centerOn(dynamic_cast<Ship*>(this->controller->getPossessed())->getGraphicsItem());
}
