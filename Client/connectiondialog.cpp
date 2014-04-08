#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    // Setup validators
    QIntValidator* portVal = new QIntValidator(0, 65535);
    this->ui->lineEditPort->setValidator(portVal);

    // Validator to for name to be only English alphanumeric characters and between 1 and 50 characters
    QRegularExpressionValidator* nameValid = new QRegularExpressionValidator(QRegularExpression("[a-z,A-Z,0-9]{1,50}"), this->ui->lineEditName);
     this->ui->lineEditName->setValidator((nameValid));

    // Allow only inputs which match an IP address to be entered
    QRegularExpressionValidator* ipValid = new QRegularExpressionValidator(QRegularExpression("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"), this->ui->lineEditAddress);
    this->ui->lineEditAddress->setValidator(ipValid);

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
