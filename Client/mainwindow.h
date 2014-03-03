#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTimer>
#include <QGraphicsView>
#include <QDebug>

#include <RenderBody>
#include <Connection>

#include "spacegraphicsscene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void messageReceived(QString username, QString message);

private:
    Ui::MainWindow *ui;
    Connection *connection;
};

#endif // MAINWINDOW_H
