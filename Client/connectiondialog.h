#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QStyleFactory>
#include <QStringList>
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>

#include <Configurator>

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
    void connectToServer(QString address, int port, QString name, QString shipName, QColor primColor, QColor secColor, QColor tertColor);

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

    /**
     * @brief updateShipImage Show the pixmap for the ship currently selected
     */
    void updateShipImage(QString);

    /**
     * @brief colorSelect When a color button is pushed, handles getting input
     */
    void colorSelectPrim();
    void colorSelectSec();
    void colorSelectTert();

private:
    Ui::ConnectionDialog *ui;
    static const QString imagePath;
    static const QString maskPath;

    // Mask colors
    QColor* color1;
    QColor* color2;
    QColor* color3;
};

#endif // CONNECTIONDIALOG_H
