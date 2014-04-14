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
    ships << "PigShip" << "BirdofPreyShip" << "KittenCupPlanet" << "ColourfulShip" << "DuckShip" << "FireflyShip" << "FlyingSaucerShip" << "PlanetTreckShip" << "RingworldPlanet" << "ShippyShip" << "SpaceShuttleShip" << "TARDISShip";
    this->ui->shipNames->addItems(ships);

    // Connect Combo box to update pixmap
    connect(this->ui->shipNames, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateShipImage(QString)));

    // Connect signals
    connect(this->ui->pushButtonJoin, SIGNAL(clicked()), this, SLOT(connectButtonClicked()));
    connect(this->ui->pushButtonQuit, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));

    // Connect color buttons to color selection slot
    connect(this->ui->primColor, SIGNAL(clicked()), this, SLOT(colorSelectPrim()));
    connect(this->ui->secColor, SIGNAL(clicked()), this, SLOT(colorSelectSec()));
    connect(this->ui->tertColor, SIGNAL(clicked()), this, SLOT(colorSelectTert()));

    // Set default values for color selection - randomize so players don't share colors too often
    this->color1 = new QColor();
    this->color1->setRed(rand() % 256);
    this->color1->setGreen(rand() % 256);
    this->color1->setBlue(rand() % 256);

    this->color2 = new QColor();
    this->color2->setRed(rand() % 256);
    this->color2->setGreen(rand() % 256);
    this->color2->setBlue(rand() % 256);

    this->color3 = new QColor();
    this->color3->setRed(rand() % 256);
    this->color3->setGreen(rand() % 256);
    this->color3->setBlue(rand() % 256);

    QPixmap* colorDisplay = new QPixmap(25, 25);
    colorDisplay->fill(*this->color1);
    this->ui->primColorImage->setPixmap(*colorDisplay);
    colorDisplay->fill(*this->color2);
    this->ui->secColorImage->setPixmap(*colorDisplay);
    colorDisplay->fill(*this->color3);
    this->ui->tertColorImage->setPixmap(*colorDisplay);

    // Set image to current label
    this->updateShipImage(this->ui->shipNames->currentText());

    // Load from config file
    QHash<QString, QString> config = Configurator::instance()->getConfig();
    if (config.contains("Address"))
        this->ui->lineEditAddress->setText(config.value("Address"));
    if (config.contains("Port"))
        this->ui->lineEditPort->setText(config.value("Port"));
    if (config.contains("Name"))
        this->ui->lineEditName->setText(config.value("Name"));
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

    // Save config
    QHash<QString, QString> config;
    config.insert("Address", this->ui->lineEditAddress->text());
    config.insert("Port", this->ui->lineEditPort->text());
    config.insert("Name", this->ui->lineEditName->text());
    Configurator::instance()->updateConfig(config);

    emit connectToServer(address, port, name, shipName, *this->color1, *this->color2, *this->color3);
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
    QImage mask(this->maskPath + shipName);

    // Colors in mask to replace in image
    // Red, Blue, Green
    QColor primaryMask;
    primaryMask.setRed(255);
    QColor secondaryMask;
    secondaryMask.setBlue(255);
    QColor tertiaryMask;
    tertiaryMask.setGreen(255);

    if (image.isNull())
    {
        QMessageBox errorBox;
        errorBox.setText("There was a problem loading asset: " + this->imagePath + shipName);
        errorBox.exec();
        return;
    }

    // Not a fatal error
    if (mask.isNull())
    {
        QMessageBox errorBox;
        errorBox.setText("There was a problem loading asset: " + this->maskPath + shipName);
        errorBox.exec();
    }

    // Loop through each pixel in the images
    for (int x = 0; x < mask.size().width(); x++)
    {
        for (int y = 0; y < mask.size().height(); y++)
        {
            // For red in mask, replace with primary
            if (mask.pixel(x, y) == primaryMask.rgb())
            {
                image.setPixel(x, y, this->color1->rgb());
            }
            // For blue in mask, replace with secondary
            else if (mask.pixel(x, y) == secondaryMask.rgb())
            {
                image.setPixel(x, y, this->color2->rgb());
            }
            // For green in mask, replace with tertiary
            else if (mask.pixel(x, y) == tertiaryMask.rgb())
            {
                image.setPixel(x, y, this->color3->rgb());
            }
        }
    }

    // Put into pixmap
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    this->ui->shipImage->setPixmap(pixmap);
}

void ConnectionDialog::colorSelectPrim()
{
    QColorDialog* primColorDiag = new QColorDialog();

    *this->color1 = primColorDiag->getColor();

    QPixmap* colorDisplay = new QPixmap(25, 25);
    colorDisplay->fill(*this->color1);

    this->ui->primColorImage->setPixmap(*colorDisplay);

    // Set image to current label
    this->updateShipImage(this->ui->shipNames->currentText());
}

void ConnectionDialog::colorSelectSec()
{
    QColorDialog* ColorDiag = new QColorDialog();

    *this->color2 = ColorDiag->getColor();

    QPixmap* colorDisplay = new QPixmap(25, 25);
    colorDisplay->fill(*this->color2);

    this->ui->secColorImage->setPixmap(*colorDisplay);

    // Set image to current label
    this->updateShipImage(this->ui->shipNames->currentText());
}

void ConnectionDialog::colorSelectTert()
{
    QColorDialog* ColorDiag = new QColorDialog();

    *this->color3 = ColorDiag->getColor();

    QPixmap* colorDisplay = new QPixmap(25, 25);
    colorDisplay->fill(*this->color3);

    this->ui->tertColorImage->setPixmap(*colorDisplay);

    // Set image to current label
    this->updateShipImage(this->ui->shipNames->currentText());
}


