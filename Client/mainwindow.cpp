#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout;
    this->ui->centralWidget->setLayout(gridLayout);

    QGraphicsView *view = new QGraphicsView();
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    SpaceGraphicsScene* space = new SpaceGraphicsScene(this);
    view->setScene(space);
    gridLayout->addWidget(view, 0, 0);

    RenderBody body;
    body.loadImageByteArray("a");
    body.createGraphic();
    body.getGraphicsItem()->setPos(-200, -200);
    space->addItem(body.getGraphicsItem());

    RenderBody body2;
    body2.loadImageByteArray("a");
    body2.createGraphic();
    body2.getGraphicsItem()->setPos(100, 100);
    space->addItem(body2.getGraphicsItem());
    view->centerOn(body2.getGraphicsItem());

    RenderBody body3;
    body3.loadImageByteArray("a");
    body3.createGraphic();
    body3.getGraphicsItem()->setPos(500, 500);
    space->addItem(body3.getGraphicsItem());

    this->connection = new Connection();

    // TODO: Host and port from config
    this->connection->connectToHost("localhost", 6886);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::message()
{
    qDebug() << "Ready fo use.";
}
