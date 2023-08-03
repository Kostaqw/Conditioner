#include "RotatingRectWidget.h"

#include <QPainter>
#include <QDebug>

RotatingRectWidget::RotatingRectWidget(int width, int height, QWidget *parent)
    : RoundedGraphics(width, height, parent), m_rotationAngle(0)
{

    setFixedSize(width, height);

    m_color = QColor("#31395e");

    m_slider = new QSlider(Qt::Vertical, this);
    m_slider->setGeometry(width /100*80, height/100*5, 30, height /100*90);
    m_slider->setMinimum(0);
    m_slider->setMaximum(110);
    m_slider->setStyleSheet("QSlider { background-color: transparent; }"
                          "QSlider::groove:vertical {"
                          "border-left: 2px solid #999999;"
                          "border-right: 2px solid #999999;"
                          "width: 12px;"
                          "background: #dddddd;"
                          "margin: 2px 0;"
                          "border-radius: 6px;"
                          "}"
                          "QSlider::handle:vertical {"
                          "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #7cc7ea, stop:1 #7cc7ea);"
                          "border: 2px solid #88cded;"
                          "width: 12px; "
                          "height: 12px;"
                          "margin-left: -5px;"
                          "margin-right: -5px;"
                          "border-radius: 6px;"
                          "}");
    connect(m_slider, &QSlider::valueChanged, this, &RotatingRectWidget::rotateRectangles);

    m_image = QPixmap("/home/kostaqw/Conditioner/img/white.png");
}

void RotatingRectWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawRectangles(&painter);
    drawAirflow(&painter);
}

void RotatingRectWidget::drawRectangles(QPainter* painter)
{
    painter->setBrush(m_color);
    painter->drawRoundedRect(rect(), 10, 10);
    drawShadow(painter, rect());
    painter->save();

    float rectWidth = width()/100*2;
    float rectHeigth = height()/100*10;

    int targetX1 = width()/100*45;
    int targetY1 = width()/100*15;
    int targetX2 = width()/100*45;
    int targetY2 = width()/100*25;
    int targetX3 = width()/100*45;
    int targetY3 = width()/100*35;

    painter->setBrush(QColor("#ffffff"));

    painter->translate(targetX1, targetY1);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    painter->setBrush(QColor("#ffffff"));
    painter->translate(targetX2 , targetY2);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    painter->setBrush(QColor("#ffffff"));
    painter->translate(targetX3 , targetY3);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();
    emit changeAngle(m_rotationAngle);

}

void RotatingRectWidget::drawAirflow(QPainter* painter)
{
    painter->save();

    int targetWidth = width() /100 * 90;
    int targetHeight = height() /100 * 90;
    QSize imageSize = m_image.size();
    imageSize.scale(targetWidth, targetHeight, Qt::KeepAspectRatio);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(width()/100*2,height()/100*2, imageSize.width(), imageSize.height(), m_image);
    painter->restore();
    /*
    painter->save();
    int centerX = width() / 2;
    int centerY = height() / 2;

    QPen pen(Qt::red);
    pen.setWidth(10);
    painter->setPen(pen);
    painter->setBrush(Qt::red);


    painter->drawRect(10, 10, width()- 70, 5);
    painter->drawRect(10, 10, 5, height() - 30); // Top
    painter->drawRect(10, height() - 20, 50, 5); // Bottom
    painter->drawLine(60, height() - 20, 90,90);
    painter->restore();
    */

}

void RotatingRectWidget::rotateRectangles(int angle)
{
    m_rotationAngle = angle;
    update();
}

void RotatingRectWidget::getAngle(int angle)
{
    m_rotationAngle = angle;
    m_slider->setValue(m_rotationAngle);
    update();
}
