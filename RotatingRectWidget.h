#pragma once


#include <QWidget>
#include <QSlider>
#include <QPixmap>
#include "RoundedGraphics.h"

class RotatingRectWidget : public RoundedGraphics
{
    Q_OBJECT
public:
    explicit RotatingRectWidget(int width, int height, QWidget *parent = nullptr);

public slots:
    void rotateRectangles(int angle);
    void getAngle(int angle);

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawRectangles(QPainter* painter);
    void drawAirflow(QPainter* painter);

private:
    int m_rotationAngle;
    QSlider* m_slider;
    QTimer* m_timer;
    QPixmap m_image;

signals:
    void changeAngle(int angle);

};
