#include "RoundedGraphichParametrs.h"

RoundedGraphichParametrs::RoundedGraphichParametrs(int width, int height, QWidget* parent) : RoundedGraphics(width, height, parent)
{
    m_color = QColor("#31395e");
}

void RoundedGraphichParametrs :: paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing);

      painter.setPen(Qt::NoPen);
      painter.setBrush(m_color);
      painter.drawRoundedRect(rect(), 10, 10);

      drawShadow(&painter, rect());

      painter.setFont(m_textFont);
      QRect textRect = QRect(width()/100*10, height()/100*20, width(), height());
      QTextOption textOption;
      textOption.setWrapMode(QTextOption::WordWrap);
      painter.setPen(Qt::white);
      painter.drawText(textRect, m_text, textOption);
}

void RoundedGraphichParametrs::getParametrs(int temp, int pressure, int humidity, int angle)
{
    m_text = "T: "+ QString::number(temp)+ " \t\t\tH: " + QString::number(humidity) + "\nP: " + QString::number(pressure) + "\t\t<: " + QString::number(angle);
    update();
}
