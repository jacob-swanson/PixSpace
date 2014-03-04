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

private slots:
    void layoutDirectionChanged(int index);
    void spacingChanged(int spacing);
    void fontChanged(const QFont &font);
    void styleChanged(const QString &styleName);

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
