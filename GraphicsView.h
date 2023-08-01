#pragma once

#include <QGraphicsView>

class GraphicsView : public QGraphicsView {
public:
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
