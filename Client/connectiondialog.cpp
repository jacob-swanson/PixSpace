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
    emit connectToServer(
                this->ui->lineEditAddress->text(),
                this->ui->lineEditPort->text().toInt(),
                this->ui->lineEditName->text());
}

void ConnectionDialog::quitButtonClicked()
{
    emit quit();
}
