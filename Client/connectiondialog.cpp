#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->layoutDirection->setCurrentIndex(layoutDirection() != Qt::LeftToRight);

    foreach (QString styleName, QStyleFactory::keys()) {
        ui->style->addItem(styleName);
        if (style()->objectName().toLower() == styleName.toLower())
            ui->style->setCurrentIndex(ui->style->count() - 1);
    }

    connect(ui->layoutDirection, SIGNAL(activated(int)),
            this, SLOT(layoutDirectionChanged(int)));
    connect(ui->spacing, SIGNAL(valueChanged(int)),
            this, SLOT(spacingChanged(int)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(fontChanged(QFont)));
    connect(ui->style, SIGNAL(activated(QString)),
            this, SLOT(styleChanged(QString)));
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::layoutDirectionChanged(int index)
{
    setLayoutDirection(index == 0 ? Qt::LeftToRight : Qt::RightToLeft);
}

void ConnectionDialog::spacingChanged(int spacing)
{
    layout()->setSpacing(spacing);
    adjustSize();
}

void ConnectionDialog::fontChanged(const QFont &font)
{
    setFont(font);
}

static void setStyleHelper(QWidget *widget, QStyle *style)
{
    widget->setStyle(style);
    widget->setPalette(style->standardPalette());
    foreach (QObject *child, widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child))
            setStyleHelper(childWidget, style);
    }
}

void ConnectionDialog::styleChanged(const QString &styleName)
{
    QStyle *style = QStyleFactory::create(styleName);
    if (style)
        setStyleHelper(this, style);
}
