#include "connectiondialog.h"
#include "ui_connectiondialog.h"

#include <QDebug>

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    // Setup validators
    QIntValidator* portVal = new QIntValidator(0, 65535);
    this->ui->lineEditPort->setValidator(portVal);

    // TODO: Validator for Name and IP

    // Connect signals
    connect(this->ui->pushButtonJoin, SIGNAL(clicked()), this, SLOT(connectButtonClicked()));
    connect(this->ui->pushButtonQuit, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::connectButtonClicked()
{
    QString address = !this->ui->lineEditAddress->text().isEmpty() ? this->ui->lineEditAddress->text() : this->ui->lineEditAddress->placeholderText();
    int port = !this->ui->lineEditPort->text().isEmpty() ? this->ui->lineEditPort->text().toInt() : this->ui->lineEditPort->placeholderText().toInt();
    QString name = !this->ui->lineEditName->text().isEmpty() ? this->ui->lineEditName->text() : this->ui->lineEditName->placeholderText();

    emit connectToServer(address, port, name);
}

void ConnectionDialog::quitButtonClicked()
{
    emit quit();
}
