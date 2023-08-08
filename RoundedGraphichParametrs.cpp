#include "RoundedGraphichParametrs.h"

/**
 * @brief Конструктор класса RoundedGraphichParametrs.
 *
 * @param width Ширина виджета.
 * @param height Высота виджета.
 * @param parent Родительский объект.
 */
RoundedGraphichParametrs::RoundedGraphichParametrs(int width, int height, QWidget* parent) : RoundedGraphics(width, height, parent)
{
    m_shadowColor = QColor("#31395e");
    m_textFont = QFont("Arial", 30);
    m_textFont.setBold(true);

    m_tempLabel = new QLabel("T: ", this);
    m_pressureLabel = new QLabel("P: ", this);
    m_humidityLabel = new QLabel("H: ", this);
    m_angleLabel = new QLabel("<",this);

    m_tempLabel->setFont(m_textFont);
    m_pressureLabel->setFont(m_textFont);
    m_humidityLabel->setFont(m_textFont);
    m_angleLabel->setFont(m_textFont);


    int labelWidth = width/100*45;
    int labelHeight = height/100*45;

    m_tempLabel->setGeometry(width/100*5, height/100*5, labelWidth, labelHeight);
    m_pressureLabel->setGeometry(width/100*5, height/100*45, labelWidth*1.05, labelHeight);
    m_humidityLabel->setGeometry(width/100*60, height/100*5, labelWidth, labelHeight);
    m_angleLabel->setGeometry(width/100*60, height/100*45, labelWidth, labelHeight);

}

/**
 * @brief Обработчик события перерисовки виджета.
 *
 * @param event Событие перерисовки.
 */
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
}

/**
 * @brief Получение угла и обновление виджета.
 *
 * @param value Значение угла.
 */
void RoundedGraphichParametrs::getAngle(int value)
{
    m_angle = value;
    updateWidget();
}

/**
 * @brief Получение параметров и обновление виджета.
 *
 * @param temp Температура.
 * @param pressure Давление.
 * @param humidity Влажность.
 * @param angle Угол.
 */
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

/**
 * @brief Обновление отображения виджета.
 */
void RoundedGraphichParametrs::updateWidget()
{
    if(Settings::instance().readSetting("theme")=="dark")
    {
        m_tempLabel->setStyleSheet("color: white;");
        m_pressureLabel->setStyleSheet("color: white;");
        m_humidityLabel->setStyleSheet("color: white;");
        m_angleLabel->setStyleSheet("color: white;");
    }
    else
    {
        m_tempLabel->setStyleSheet("color: black;");
        m_pressureLabel->setStyleSheet("color: black;");
        m_humidityLabel->setStyleSheet("color: black;");
        m_angleLabel->setStyleSheet("color: black;");
    }

  QString temper;
  QString pressure;
  if(Settings::instance().readSetting("temperature", "") == "C")
    {
       m_tempLabel->setText("T: "+ QString::number(m_temp_c) + "°C");
    }
  else if(Settings::instance().readSetting("temperature", "") == "F")
    {
       m_tempLabel->setText("T: "+ QString::number(m_temp_f) + "°F");
    }
  else
    {
       m_tempLabel->setText("T: "+ QString::number(m_temp_k) + "K");
    }

  if(Settings::instance().readSetting("pressure", "") == "Mm")
    {
       m_pressureLabel->setText("P: " + QString::number(m_pres_mm) + "Mm");
    }
  else
    {
       m_pressureLabel->setText("P: " + QString::number(m_pres_p/1000) + " kP");
    }

    m_humidityLabel->setText("H: " + QString::number(m_hum) + "%");
    m_angleLabel->setText("<: " + QString::number(m_angle)+"°");

    update();
}
