#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QtGlobal>
#include <QObject>
#include <QMessageBox>

#include <Configurator>

#include "serverapp.h"

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);

    // Setup database
    QHash<QString, QString> config = Configurator::instance()->getConfig();
    if (config.contains("Hostname"))
        DataManager::instance()->setHostName(config.value("Hostname"));
    else
        DataManager::instance()->setHostName("localhost");

    if (config.contains("Port"))
        DataManager::instance()->setPort(config.value("Port").toInt());
    else
        DataManager::instance()->setPort(6886);

    if (config.contains("Database"))
        DataManager::instance()->setDatabaseName(config.value("Database"));
    else
        DataManager::instance()->setDatabaseName("pixspace");

    if (config.contains("Username"))
        DataManager::instance()->setUserName(config.value("Username"));
    else
        DataManager::instance()->setUserName("pixspace");

    if (config.contains("Password"))
        DataManager::instance()->setPassword(config.value("Password"));
    else
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
