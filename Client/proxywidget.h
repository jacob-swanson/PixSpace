#ifndef PROXYWIDGET_H
#define PROXYWIDGET_H

#include <QTimeLine>
#include <QGraphicsProxyWidget>

class CustomProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    explicit CustomProxy(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    QRectF boundingRect() const;
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private slots:
    void updateStep(qreal step);
    void stateChanged(QTimeLine::State);
    void zoomIn();
    void zoomOut();

private:
    QTimeLine *timeLine;
    bool popupShown;
    QGraphicsItem *currentPopup;
};

#endif // PROXYWIDGET_H
