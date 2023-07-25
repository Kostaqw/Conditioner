#include "RoundedGraphicsWithSlider.h"
#include <QStyle>

RoundedGraphicsWithSlider::RoundedGraphicsWithSlider(int width, int height, QWidget* parent)
    : RoundedGraphics(width, height, parent)
{
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setGeometry(20, 70, width - 40, 20);
    m_slider->setStyleSheet("QSlider { background-color: transparent; }"
                            "QSlider::groove:horizontal {"
                            "border-top: 2px solid #999999;"
                            "border-bottom: 2px solid #999999;"
                            "height: 3px;"
                            "background: #dddddd;"
                            "margin: 2px 0;"
                            "}"
                            "QSlider::handle:horizontal {"
                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #7cc7ea, stop:1 #7cc7ea);"
                            "border: 2px solid #88cded;"
                            "width: 8px; "
                            "height: 8px;"
                            "margin-top: -5px;"
                            "margin-bottom: -5px;"
                            "border-radius: 5px;"
                            "}");
    m_slider->setMaximum(45);
    m_slider->setMinimum(10);
    m_slider->setValue(25);
    SetText(QString::number(m_slider->value()) + " C");
    connect(m_slider, &QSlider::valueChanged, this, &RoundedGraphicsWithSlider::handleSliderValueChanged);
}

void RoundedGraphicsWithSlider::handleSliderValueChanged(int value)
{
    SetText(QString::number(value) + " C");
    update();
}
