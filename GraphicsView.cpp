#include "GraphicsView.h"
#include <QGraphicsView>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);


    int width = parentWidget()->width();
    int height = parentWidget()->height();

    qreal scaleFactor = qMin(width / qreal(scene()->width()), height / qreal(scene()->height()));
    this->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
}
