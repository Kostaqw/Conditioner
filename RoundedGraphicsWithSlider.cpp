#include "RoundedGraphicsWithSlider.h"


/**
 * @brief Конструктор класса RoundedGraphicsWithSlider.
 *
 * @param width Ширина графического элемента.
 * @param height Высота графического элемента.
 * @param parent Родительский виджет.
 */

RoundedGraphicsWithSlider::RoundedGraphicsWithSlider(int width, int height, QWidget* parent)
    : RoundedGraphics(width, height, parent)
{
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setGeometry(20, height/100*80, width - 40, 20);
    m_slider->setStyleSheet("QSlider { background-color: transparent; }"
                            "QSlider::groove:horizontal {"
                            "border-top: 2px solid #999999;"
                            "border-bottom: 2px solid #999999;"
                            "height: 12px;"
                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00bfff, stop:1 #ff0000);"
                            "margin: 2px 0;"
                            "border-radius: 6px;"
                            "}"
                            "QSlider::handle:horizontal {"
                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #7cc7ea, stop:1 #7cc7ea);"
                            "border: 2px solid #88cded;"
                            "width: 12px; "
                            "height: 12px;"
                            "margin-top: -5px;"
                            "margin-bottom: -5px;"
                            "border-radius: 6px;"
                            "}");
    m_slider->setMaximum(45);
    m_slider->setMinimum(10);
    m_slider->setValue(25);
    SetText(QString::number(m_slider->value()) + " C");
    connect(m_slider, &QSlider::valueChanged, this, &RoundedGraphicsWithSlider::handleSliderValueChanged);
}

/**
 * @brief Слот, вызывающийся при изменении значения QSlider.
 *
 * @param value Новое значение QSlider.
 */
void RoundedGraphicsWithSlider::handleSliderValueChanged(int value)
{
    SetText(QString::number(value) + " C");
    emit sendTemp(value);
    update();
    Settings::instance().writeSetting("setTemp",QString::number(value));
}

/**
 * @brief Устанавливает значение QSlider для температуры.
 *
 * @param value Значение температуры.
 */
void RoundedGraphicsWithSlider::setTemp(int value)
{
    m_slider->setValue(value);
    update();
}
