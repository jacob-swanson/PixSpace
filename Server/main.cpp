#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QtGlobal>
#include <QObject>
#include <QMessageBox>

#include <signal.h>

#include "serverapp.h"

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);

    // Setup database
    DataManager::instance()->setHostName("localhost");
    DataManager::instance()->setHostName("localhost");
    DataManager::instance()->setPort(3306);
    DataManager::instance()->setDatabaseName("pixspace");
    DataManager::instance()->setUserName("pixspace");
    DataManager::instance()->setPassword("pixspace");
    // Connect to DB, connect and check for error, if failed report error and close
    if (!DataManager::instance()->connect())
    {
        QMessageBox errorMessage;
        errorMessage.setText("PixSpace Server has failed to launch.");
        errorMessage.setInformativeText("Error reported by Database was:\n" + DataManager::instance()->getLastError());
        errorMessage.setIcon(QMessageBox::Warning);
        errorMessage.exec();
        return 0;
    }

    ServerApp app;
    app.show();

    QObject::connect(&app, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, &app, SLOT(start()));

    return a.exec();
}
