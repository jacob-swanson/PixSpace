#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"

#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Widget *native = new Widget(&helper, this);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(native, 0, 0);
    this->ui->centralWidget->setLayout(gridLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
