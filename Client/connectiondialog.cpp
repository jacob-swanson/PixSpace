#include "connectiondialog.h"
#include "ui_connectiondialog.h"

const QString ConnectionDialog::imagePath = ":/bodies/";
const QString ConnectionDialog::maskPath = ":/bodies-mask/";

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

    // Put ships names in a QStringList
    QStringList ships;
    ships << "PigShip" << "ColourfulShip" << "DuckShip" << "FireflyShip" << "FlyingSaucerShip" << "PlanetTreckShip" << "RingworldPlanet" << "ShippyShip" << "SpaceShuttleShip";
    this->ui->shipNames->addItems(ships);

    // Connect Combo box to update pixmap
    connect(this->ui->shipNames, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateShipImage(QString)));

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
    QString shipName = this->ui->shipNames->currentText();

    emit connectToServer(address, port, name, shipName);
}

void ConnectionDialog::quitButtonClicked()
{
    emit quit();
}

void ConnectionDialog::updateShipImage(QString shipName)
{
    // Get image of ship
    QImage image(this->imagePath + shipName);

    // Apply current mask

    // Put into pixmap
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    this->ui->shipImage->setPixmap(pixmap);
}
