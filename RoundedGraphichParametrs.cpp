#include "RoundedGraphichParametrs.h"

RoundedGraphichParametrs::RoundedGraphichParametrs(int width, int height, QWidget* parent) : RoundedGraphics(width, height, parent)
{
    m_shadowColor = QColor("#31395e");

    m_textFont = QFont("Arial", 30);
    m_textFont.setBold(true);
}

void RoundedGraphichParametrs :: paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing);

      painter.setPen(Qt::NoPen);
      painter.setBrush(m_shadowColor);
      painter.drawRoundedRect(rect(), 10, 10);

      drawMainRectangle(&painter, rect());

      painter.setFont(m_textFont);
      QRect textRect = QRect(width()/100*10, height()/100*20, width(), height());
      QTextOption textOption;
      textOption.setWrapMode(QTextOption::WordWrap);

      if(Settings::instance().readSetting("theme")=="dark")
      {
       painter.setPen(Qt::white);
      }
      else
      {
       painter.setPen(Qt::black);
      }

      painter.drawText(textRect, m_text, textOption);
}

void RoundedGraphichParametrs::getAngle(int value)
{
    m_angle = value;
    updateWidget();
}

void RoundedGraphichParametrs::getParametrs(int temp, int pressure, int humidity, int angle)
{
  m_temp_c = temp;
  m_temp_f = (temp*9/5)+32;
  m_temp_k = temp-273;

  m_pres_mm = pressure;
  m_pres_p = pressure * 133;

  m_hum = humidity;
  m_angle = angle;

  updateWidget();
}

void RoundedGraphichParametrs::updateWidget()
{

  QString temper;
  QString pressure;
  if(Settings::instance().readSetting("temperature", "") == "C")
    {
       temper = "T: "+ QString::number(m_temp_c) + "°C";
    }
  else if(Settings::instance().readSetting("temperature", "") == "F")
    {
       temper = "T: "+ QString::number(m_temp_f) + "°F";
    }
  else
    {
       temper = "T: "+ QString::number(m_temp_k) + "K";
    }

  if(Settings::instance().readSetting("pressure", "") == "Mm")
    {
       pressure = "P: " + QString::number(m_pres_mm) + "Mm";
    }
  else
    {
       pressure = "P: " + QString::number(m_pres_p) + "P";
    }

  m_text = temper+ " \t\t\tH: " + QString::number(m_hum) + "%" + "\n" + pressure + "\t\t<: " + QString::number(m_angle)+"°";
  update();
}
