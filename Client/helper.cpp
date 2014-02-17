#include "helper.h"

#include <QPainter>
#include <QPaintEvent>

Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    // Draw stuff
}
