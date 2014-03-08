#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGlobal>

#include "clientapp.h"

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);

    ClientApp client;

    client.show();

    return a.exec();
}
