#include "GraphicsView.h"
#include <QGraphicsView>

/**
 * @brief Конструктор класса GraphicsView.
 * @param scene Указатель на QGraphicsScene, которая будет отображаться в виджете.
 * @param parent Указатель на родительский виджет.
 */
GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {}

/**
 * @brief Обработчик события изменения размера виджета.
 * @param event Указатель на событие изменения размера.
 */

void GraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);


    int width = parentWidget()->width();
    int height = parentWidget()->height();

    qreal scaleFactor = qMin(width / qreal(scene()->width()), height / qreal(scene()->height()));
    this->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
}
