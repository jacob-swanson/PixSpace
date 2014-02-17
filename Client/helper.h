#ifndef HELPER_H
#define HELPER_H

#include <QFont>
#include <QPen>
#include <QPaintEvent>
#include <QBrush>

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QFont textFont;
    QPen textPen;
    QBrush background;
    QPixmap ship;
};

#endif
