#include "serverapp.h"

int ServerApp::sighupFd[2];
int ServerApp::sigtermFd[2];
int ServerApp::sigintFd[2];

ServerApp::ServerApp(QObject *parent) :
    QObject(parent)
{
    // Create socket pairs for SIGHUP, SIGTERM, and SIGINT
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sighupFd))
       qFatal("Couldn't create HUP socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
       qFatal("Couldn't create TERM socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigintFd))
       qFatal("Couldn't create INT socketpair");

    // Create Qt socket notifiers
    snHup = new QSocketNotifier(sighupFd[1], QSocketNotifier::Read, this);
    connect(snHup, SIGNAL(activated(int)), this, SLOT(handleSigHup()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleSigTerm()));
    snInt = new QSocketNotifier(sigintFd[1], QSocketNotifier::Read, this);
    connect(snInt, SIGNAL(activated(int)), this, SLOT(handleSigInt()));

    // Create objects
    this->universe = new Universe();

    // Load save data
    this->universe->setBodies(this->datamanager->loadBodies());

    // Start listening
    this->server = new NetworkServer(this);
    // TODO: Get port from config
    this->server->listen(QHostAddress::Any, 6886);

    qDebug() << "Listening on: " << this->server->serverAddress().toString() << ":" << this->server->serverPort();

    // Connect signals for TCP server
    connect(server, SIGNAL(newConnection(Connection*)), this, SLOT(displayConnection(Connection*)));
    connect(server, SIGNAL(disconnection(QString)), this, SLOT(displayDisconnection(QString)));

    // Setup timers
    tickTimer.setInterval(16);
    connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
}

void ServerApp::tick()
{
    // Main server loop
    // Calculate time since last tick in ms
    double deltaTime = ((double)timer.restart()/1000.0);

    // Update the simulation
    universe->simulateStep(deltaTime);
    datamanager->saveBodies(universe->getBodies());
}

void ServerApp::start()
{
    // Start the simulation
    qDebug() << "Starting simulation...";

    tickTimer.start();
    timer.start();
}

void ServerApp::stop()
{
    // Stop the simulation
    tickTimer.stop();
    qDebug() << "Stopped simulation.";

    datamanager->saveBodies(universe->getBodies());
    qDebug() << "Saved.";

    emit(finished());
}

// Unix signal handlers
void ServerApp::hupSignalHandler(int)
{
    char a = 1;
    ::write(sighupFd[0], &a, sizeof(a));
}

void ServerApp::termSignalHandler(int)
{
    char a = 1;
    ::write(sigtermFd[0], &a, sizeof(a));
}

void ServerApp::intSignalHandler(int)
{
    char a = 1;
    ::write(sigintFd[0], &a, sizeof(a));
}

// Qt SLOTs handlers
void ServerApp::handleSigTerm()
{
    snTerm->setEnabled(false);
    char tmp;
    ::read(sigtermFd[1], &tmp, sizeof(tmp));

    // Do stuff here
    this->stop();

    snTerm->setEnabled(true);
}

void ServerApp::handleSigHup()
{
    snHup->setEnabled(false);
    char tmp;
    ::read(sighupFd[1], &tmp, sizeof(tmp));

    // Do stuff here
    this->stop();

    snHup->setEnabled(true);
}

void ServerApp::handleSigInt()
{
    snInt->setEnabled(false);
    char tmp;
    ::read(sigintFd[1], &tmp, sizeof(tmp));

    // Do stuff here
    this->stop();

    snInt->setEnabled(true);
}

void ServerApp::displayConnection(Connection *connection)
{
    qDebug() << "User Connected: " << connection->getName();
}

void ServerApp::displayDisconnection(QString username)
{
    qDebug() << "User Disconnected: " << username;
}
