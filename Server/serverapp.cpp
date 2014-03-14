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

    // Get data from data manager fro labels in GUI
        this->ui->sqlDBName->setText(DataManager::instance()->getDatabaseName());
        this->ui->sqlHost->setText(DataManager::instance()->getHostName());
        this->ui->sqlPort->setText(QString::number(DataManager::instance()->getPort()));
        this->ui->sqlUserName->setText(DataManager::instance()->getUserName());

    // Connect the DB save button to update function
        connect(this->ui->saveSQL, SIGNAL(clicked()), this, SLOT(updateSQLConfig()));

    // Setup speed labels and current position of slider
        this->ui->speedLabel->setText("Current Time Acceleration:   " + QString::number(this->universe->getTimeAcceleration()));
        this->ui->speedSlider->setSliderPosition(6);
        this->updateNewSpeedLabel(10000);

        // Connect slider to slot to update to a new speed value
        connect (this->ui->speedSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateNewSpeedValue(int)));

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
        this->updateNewSpeedLabel(100);
        break;
    case 4:
        this->updateNewSpeedLabel(1000);
        break;
    case 5:
        this->updateNewSpeedLabel(10000);
        break;
    case 6:
        this->updateNewSpeedLabel(100000);
        break;
    }
}

void ServerApp::updateNewSpeedLabel(int speed)
{
    this->ui->newSpeedLabel->setText("New Time Acceleration:        " + QString::number(speed));
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

    // TODO: Write to file
}
