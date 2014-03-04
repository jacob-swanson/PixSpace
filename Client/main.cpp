#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <RenderBody>

#include "spacegraphicsscene.h"
#include "proxywidget.h"
#include "connectiondialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsView view;
    view.setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    SpaceGraphicsScene space;
    view.setScene(&space);

    CustomProxy* proxy = new CustomProxy(0, Qt::Window);
    proxy->setWidget(new ConnectionDialog);

    QRectF rect = proxy->boundingRect();

    proxy->setPos(0, 0);
    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    space.addItem(proxy);

//    RenderBody body2;
//    body2.loadImageByteArray("a");
//    body2.createGraphic();
//    body2.getGraphicsItem()->setPos(100, 100);
//    space.addItem(body2.getGraphicsItem());
//    view.centerOn(body2.getGraphicsItem());

    view.show();

    return a.exec();
}
