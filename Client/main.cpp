#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "clientapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientApp client;

    client.show();

    return a.exec();
}
