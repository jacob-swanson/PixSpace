#include "serverapp.h"
#include "ui_serverapp.h"
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QHash>

ServerApp::ServerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerApp)
{
    ui->setupUi(this);

    // Create objects
    this->universe = new Universe();

    // Get data from data manager for labels in GUI
    this->ui->sqlDBName->setText(DataManager::instance()->getDatabaseName());
    this->ui->sqlHost->setText(DataManager::instance()->getHostName());
    this->ui->sqlPort->setText(QString::number(DataManager::instance()->getPort()));
    this->ui->sqlUserName->setText(DataManager::instance()->getUserName());

    // Connect the DB save button to update function
    connect(this->ui->saveSQL, SIGNAL(clicked()), this, SLOT(updateSQLConfig()));

    // Setup speed labels and current position of slider
    this->ui->speedLabel->setText("Current Time Acceleration:   " + QString::number(this->universe->getTimeAcceleration()));
    this->ui->speedSlider->setSliderPosition(0);
    this->updateNewSpeedValue(this->ui->speedSlider->sliderPosition());

    // Connect up the apply button
    connect(this->ui->applySpeed, SIGNAL(clicked()), this, SLOT(updateTimeAccelerationRequest()));

    // Connect slider to slot to update to a new speed value
    connect (this->ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(updateNewSpeedValue(int)));

    // Load save data
    this->universe->setBodies(DataManager::instance()->loadBodies());

    // Start listening
    this->server = new NetworkServer(this);
    // TODO: Get port from config
    // Set port and display it
    bool success =this->server->listen(QHostAddress::Any, 6886);
    if (!success)
    {
        QMessageBox errorMessage;
        errorMessage.setText("PixSpace Server has failed to launch.");
        errorMessage.setInformativeText("PixSpace Server was unable to bind to port 6886.");
        errorMessage.setIcon(QMessageBox::Warning);
        errorMessage.exec();
    }
    this->ui->serverPort->setText(QString::number(6886));

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

    // Emit a tick with the current slider position to perform acceleration update
    emit endTick(this->ui->speedSlider->sliderPosition());
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
    // Output message to server
    ui->serverMessage->append("User Connected: " + connection->getName());

    // clear connected users tab
    ui->connectedUsers->clear();

    // Output all connected users on tab
   ui->connectedUsers->setText(this->server->getConnectedUsers());

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

    // clear connected users tab
    ui->connectedUsers->clear();

    // Output all connected users on tab
   ui->connectedUsers->setText(this->server->getConnectedUsers());
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

void ServerApp::updateNewSpeedValue(int speed)
{
    // Map the current position of the slider to the time acceleration values
    switch (speed)
    {
        // Real time
    case 0:
        this->updateNewSpeedLabel(1);
        break;
    case 1:
        this->updateNewSpeedLabel(5);
        break;
    case 2:
        this->updateNewSpeedLabel(10);
        break;
    case 3:
        this->updateNewSpeedLabel(50);
        break;
    case 4:
        this->updateNewSpeedLabel(100);
        break;
    case 5:
        this->updateNewSpeedLabel(1000);
        break;
    case 6:
        this->updateNewSpeedLabel(10000);
        break;
    case 7:
        this->updateNewSpeedLabel(100000);
        break;
    }
}

void ServerApp::updateNewSpeedLabel(int speed)
{
    this->ui->newSpeedLabel->setText("New Time Acceleration:        " + QString::number(speed));
}

void ServerApp::updateTimeAcceleration(int speed)
{
    disconnect(this, SIGNAL(endTick(int)), this, SLOT(updateTimeAcceleration(int)));
    // Map the current position of the slider to the time acceleration values
    switch (speed)
    {
        // Real time
    case 0:
        this->universe->setTimeAcceleration((double) 1);
        break;
    case 1:
        this->universe->setTimeAcceleration((double) 5);
        break;
    case 2:
        this->universe->setTimeAcceleration((double) 10);
        break;
    case 3:
        this->universe->setTimeAcceleration((double) 50);
        break;
    case 4:
        this->universe->setTimeAcceleration((double) 100);
        break;
    case 5:
        this->universe->setTimeAcceleration((double) 1000);
        break;
    case 6:
        this->universe->setTimeAcceleration((double) 10000);
        break;
    case 7:
        this->universe->setTimeAcceleration((double) 100000);
        break;
    }
    // Update GUI
    this->ui->speedLabel->setText("Current Time Acceleration:   " + QString::number(this->universe->getTimeAcceleration()));
}

void ServerApp::updateSQLConfig()
{
    // Inform user action is being taken
    QMessageBox applyingSave;
    applyingSave.setText("Now updating the MySQL portion of server config file.");
    applyingSave.setInformativeText("You must restart for these changes to take effect.");
    applyingSave.setIcon(QMessageBox::Information);
    applyingSave.exec();

    // Kick out server message about configuration
    this->ui->serverMessage->append("Updated SQL Configuration:");
    this->ui->serverMessage->append("\tHostname: " + this->ui->sqlHost->text());
    this->ui->serverMessage->append("\tPort:     " + this->ui->sqlPort->text());
    this->ui->serverMessage->append("\tDatabase: " + this->ui->sqlDBName->text());
    this->ui->serverMessage->append("\tUsername: " + this->ui->sqlUserName->text());
    this->ui->serverMessage->append("\tPassword: *********");


    QHash<QString, QString> config;
    config.insert("Hostname", this->ui->sqlHost->text());
    config.insert("Port", this->ui->sqlPort->text());
    config.insert("Database", this->ui->sqlDBName->text());
    config.insert("Username", this->ui->sqlUserName->text());
    config.insert("Password", this->ui->sqlPass->text());

    //can test this by manually making file config.dat read only
    //error message let's you know file is unavailable for editing

    Configurator::instance()->updateConfig(config);
}

void ServerApp::updateTimeAccelerationRequest()
{
    // Request that time acceleration be updated at the end of the next tick
    connect(this, SIGNAL(endTick(int)), this, SLOT(updateTimeAcceleration(int)));
}
