#include "RotatingRectWidget.h"

#include <QPainter>
#include <QDebug>

RotatingRectWidget::RotatingRectWidget(int width, int height, QWidget *parent)
    : QWidget(parent), m_rotationAngle(0)
{
    setFixedSize(width, height);

    m_slider = new QSlider(Qt::Vertical, this);
    m_slider->setGeometry(width - 40, 10, 30, height - 20);
    connect(m_slider, &QSlider::valueChanged, this, &RotatingRectWidget::rotateRectangles);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        rotateRectangles(m_slider->value());
    });
    m_timer->start(50);
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

    painter->save();

    int centerX = width() / 2;
    int centerY = height() / 2;

    float rectWidth = width()/100*2;
    float rectHeigth = height()/100*10;

    int targetX1 = width()/100*45;
    int targetY1 = width()/100*10;
    int targetX2 = width()/100*45;
    int targetY2 = width()/100*20;
    int targetX3 = width()/100*45;
    int targetY3 = width()/100*30;

    painter->setBrush(QColor("#ffffff"));

    //painter->setPen(Qt::NoPen);

    painter->save();
    painter->translate(targetX1 + width() / 100, targetY1 + height() / 100);
    painter->rotate(-50);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    painter->translate(targetX2 + width() / 100, targetY2 + height() / 100);
    painter->rotate(-50);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    painter->translate(targetX3 + width() / 100, targetY3 + height() / 100);
    painter->rotate(-50);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();
    /*
    for (int i = 0; i < 3; ++i) {
        painter->translate(centerX, centerY);
        painter->rotate(m_rotationAngle);
        painter->setBrush(QColor(100 + i * 30, 100 + i * 30, 100 + i * 30));
        painter->drawRect(-30, -10, 60, 20);

        painter->translate(-centerX, -centerY);
    }
    */
    painter->restore();
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
    painter->restore();*/

}

void RotatingRectWidget::rotateRectangles(int angle)
{
    m_rotationAngle = angle;
    update();
}
