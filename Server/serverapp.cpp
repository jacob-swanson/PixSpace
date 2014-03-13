#include "serverapp.h"
#include "ui_serverapp.h"
#include <QMessageBox>

ServerApp::ServerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerApp)
{
    ui->setupUi(this);

    // Create objects
        this->universe = new Universe();

        this->ui->speedDisplay->setText(QString::number(this->universe->getTimeAcceleration()));

        // Load save data
        this->universe->setBodies(DataManager::instance()->loadBodies());

        // Start listening
        this->server = new NetworkServer(this);
        // TODO: Get port from config
        this->server->listen(QHostAddress::Any, 6886);

        ui->serverMessage->append("Listening on: " + this->server->serverAddress().toString() + ":" + QString::number(this->server->serverPort()));

        // Connect signals for TCP server
        connect(server, SIGNAL(newConnection(Connection*)), this, SLOT(displayConnection(Connection*)));
        connect(server, SIGNAL(disconnection(QString)), this, SLOT(displayDisconnection(QString)));
        connect(this->universe, SIGNAL(stepFinished()), this, SLOT(broadcastBodies()));
        connect(server, SIGNAL(newMessage(QString,QString)), this, SLOT(receiveMessage(QString,QString)));

        // Connect quit button to stop
        connect(ui->quitServerButton, SIGNAL(clicked()), this, SLOT(stop()));

        // Setup timers
        // TODO: Get time from the config
        tickTimer.setInterval(30);
        connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
}

ServerApp::~ServerApp()
{
    delete ui;
}

void ServerApp::tick()
{
    // Main server loop
    // Calculate time since last tick in ms
    double deltaTime = ((double)timer.restart()/1000.0);

    // Update the simulation
    universe->simulateStep(deltaTime);
}

void ServerApp::start()
{
    // Start the simulation
    ui->serverMessage->append("Starting simulation...");

    tickTimer.start();
    timer.start();
}

void ServerApp::stop()
{
    // Dialog to confirm with user
    QMessageBox confirmQuit;
    confirmQuit.setText("Are you sure you want to quit?");
    confirmQuit.setInformativeText("Continuing will disconnect all users.");
    confirmQuit.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    // Run dialog and get response
    int confirmation = confirmQuit.exec();

    // Stop the simulation if user hit OK
    if (confirmation == QMessageBox::Ok)
    {
        tickTimer.stop();
        ui->serverMessage->append("Stopped simulation.");
        DataManager::instance()->saveBodies(universe->getBodies());
        ui->serverMessage->append("Saved.");

        QMessageBox closeBox;
        closeBox.setText("The server will now exit.");
        closeBox.setStandardButtons(QMessageBox::Ok);
        closeBox.exec();

        emit(finished());
    }
    // Otherwise continue
}



void ServerApp::displayConnection(Connection *connection)
{
    ui->serverMessage->append("User Connected: " + connection->getName());
}

void ServerApp::displayDisconnection(QString username)
{
    ui->serverMessage->append("User Disconnected: " + username);

    // Get rid of their ship
    for (int i = 0; i < this->universe->getBodies().count(); i++)
    {
        Ship* ship = dynamic_cast<Ship*>(this->universe->getBodies().at(i));
        if (ship != NULL)
        {
            if (ship->getOwner() == username)
            {
                this->universe->removeBody(ship);
            }
        }
    }
}

void ServerApp::broadcastBodies()
{
    QJsonObject universeObject;
    this->universe->write(universeObject);

    QJsonDocument jsonDocument(universeObject);
    this->server->broadcastJson(jsonDocument.toJson());
}

void ServerApp::receiveMessage(QString username, QString message)
{
    QJsonParseError error;
    QJsonDocument shipDocument = QJsonDocument::fromJson(message.toLocal8Bit(), &error);

    if (!error.error)
    {
        QJsonObject shipObject = shipDocument.object();

        Body* b = NULL;
        foreach(Body* body, this->universe->getBodies())
        {
            if (body->getId() == shipObject["id"].toInt())
            {
                b = body;
            }
        }

        if (b == NULL)
        {
            b = new Ship();
            this->universe->pushBodies(b);
        }

        b->read(shipObject);
    }
    else
    {
        ui->serverMessage->append("Error parsing JSON: " + error.errorString());
    }
}
