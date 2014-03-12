#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QtGlobal>
#include <QObject>

#include <signal.h>

#include "serverapp.h"

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);

    ServerApp app;
    app.show();

    QObject::connect(&app, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, &app, SLOT(start()));

    return a.exec();
}
