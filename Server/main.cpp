#include <QCoreApplication>
#include <QTimer>
#include <signal.h>
#include <QDebug>
#include <ServerApp>

// Source: http://qt-project.org/doc/qt-5/unix-signals.html
static int setup_unix_signal_handlers()
{
    struct sigaction hup, term, sigint;

    hup.sa_handler = ServerApp::hupSignalHandler;
    sigemptyset(&hup.sa_mask);
    hup.sa_flags = 0;
    hup.sa_flags |= SA_RESTART;

    if (sigaction(SIGHUP, &hup, 0) > 0)
       return 1;

    term.sa_handler = ServerApp::termSignalHandler;
    sigemptyset(&term.sa_mask);
    term.sa_flags |= SA_RESTART;

    if (sigaction(SIGTERM, &term, 0) > 0)
       return 2;

    sigint.sa_handler = ServerApp::intSignalHandler;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags |= SA_RESTART;

    if (sigaction(SIGINT, &sigint, 0) > 0)
       return 3;

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setup_unix_signal_handlers();

    ServerApp* app = new ServerApp(&a);
    QObject::connect(app, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, app, SLOT(start()));

    return a.exec();
}
