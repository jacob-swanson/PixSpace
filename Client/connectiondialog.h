#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QStyleFactory>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

signals:
    /**
     * @brief connectToServer Emitted with new connection details
     * @param address
     * @param port
     * @param name
     */
    void connectToServer(QString address, int port, QString name);

    /**
     * @brief quit Emitted when the "Quit Game" button is pressed
     */
    void quit();

private slots:
    /**
     * @brief connectButtonClicked Handle the connect button click event, emits connectToServer()
     */
    void connectButtonClicked();

    /**
     * @brief quitButtonClicked Handle the quit button click event, emits quit()
     */
    void quitButtonClicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
