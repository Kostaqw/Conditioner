#include "RotatingRectWidget.h"

/**
 * @brief Конструктор класса RotatingRectWidget.
 * @param width Ширина виджета.
 * @param height Высота виджета.
 * @param parent Родительский виджет.
 */
RotatingRectWidget::RotatingRectWidget(int width, int height, QWidget *parent)
    : RoundedGraphics(width, height, parent), m_rotationAngle(0)
{

    setFixedSize(width, height);

    m_shadowColor = QColor("#31395e");

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

    m_whiteImage = QPixmap(":/img/img/white.png");
    m_blackImage = QPixmap(":/img/img/black.png");
}

/**
 * @brief Обработчик события рисования виджета.
 * @param event Указатель на событие рисования.
 */
void RotatingRectWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawRectangles(&painter);
    drawAirflow(&painter);
}

/**
 * @brief Отрисовка вращения прямоугольников.
 * @param painter Указатель на объект QPainter.
 */
void RotatingRectWidget::drawRectangles(QPainter* painter)
{
    painter->setBrush(m_shadowColor);
    painter->drawRoundedRect(rect(), 10, 10);
    drawMainRectangle(painter, rect());
    painter->save();

    float rectWidth = width()/100*2;
    float rectHeigth = height()/100*10;

    int targetX1 = width()/100*52;
    int targetY1 = width()/100*15;
    int targetX2 = width()/100*52;
    int targetY2 = width()/100*25;
    int targetX3 = width()/100*52;
    int targetY3 = width()/100*35;

    if(Settings::instance().readSetting("theme")=="light")
    {
        painter->setBrush(QColor("#000000"));

    }
    else
    {
        painter->setBrush(QColor("#ffffff"));
    }
    painter->translate(targetX1, targetY1);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    if(Settings::instance().readSetting("theme")=="light")
    {
        painter->setBrush(QColor("#000000"));

    }
    else
    {
        painter->setBrush(QColor("#ffffff"));
    }
    painter->translate(targetX2 , targetY2);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();

    painter->save();
    if(Settings::instance().readSetting("theme")=="light")
    {
        painter->setBrush(QColor("#000000"));

    }
    else
    {
        painter->setBrush(QColor("#ffffff"));
    }
    painter->translate(targetX3 , targetY3);
    painter->rotate(-m_rotationAngle);
    painter->drawRect(-rectWidth / 2, -rectHeigth / 2, rectWidth, rectHeigth);
    painter->restore();
    emit changeAngle(m_rotationAngle);

}

/**
 * @brief Отрисовка схему кондиционера.
 * @param painter Указатель на объект QPainter.
 */
void RotatingRectWidget::drawAirflow(QPainter* painter)
{
    painter->save();

    int targetWidth = width() /100 * 90;
    int targetHeight = height() /100 * 90;
    QSize imageSize = m_blackImage.size();
    imageSize.scale(targetWidth, targetHeight, Qt::KeepAspectRatio);

    painter->setRenderHint(QPainter::Antialiasing);
    if(Settings::instance().readSetting("theme")=="light")
    {
        painter->drawPixmap(width()/100*2,height()/100*2, imageSize.width(), imageSize.height(), m_blackImage);

    }
    else
    {
        painter->drawPixmap(width()/100*2,height()/100*2, imageSize.width(), imageSize.height(), m_whiteImage);
    }

    painter->restore();

}

/**
 * @brief Поворачивает прямоугольники на заданный угол.
 * @param angle Угол поворота.
 */
void RotatingRectWidget::rotateRectangles(int angle)
{
    m_rotationAngle = angle;
    update();
}

/**
 * @brief Устанавливает угол поворота прямоугольников.
 * @param angle Угол поворота.
 */
void RotatingRectWidget::getAngle(int angle)
{
    m_rotationAngle = angle;
    m_slider->setValue(m_rotationAngle);
    update();
}
