#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <QObject>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include <RenderBody>
#include <Connection>

#include "connectiondialog.h"

class ClientApp : public QObject
{
    Q_OBJECT
public:
    explicit ClientApp(QObject *parent = 0);

signals:

public slots:
    /**
     * @brief show Display the Game
     */
    void show();

private slots:
    /**
     * @brief connectToServer Connect to the given server
     * @param address
     * @param port
     * @param name
     */
    void connectToServer(QString address, int port, QString name);

    /**
     * @brief exitClient Exit the application
     */
    void exitClient();

    /**
     * @brief connectionSuccessful The connection to the server was successful
     */
    void connectionSuccessful();

    /**
     * @brief displayConnectionError Print out a connection error, destroy the connection, and open the connection dialog
     */
    void displayConnectionError();

    /**
     * @brief showConnectionDialog Show the connection dialog
     */
    void showConnectionDialog();

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    Connection* connection;
};

#endif // CLIENTAPP_H
