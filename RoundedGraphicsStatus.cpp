#include "RoundedGraphicsStatus.h"
#include "Settings.h"

RoundedGraphicsStatus::RoundedGraphicsStatus(int width, int height, QWidget* parent)
    : RoundedGraphics(width, height, parent)
{
   CreateStatusMap();
   m_shadowColor = QColor("#31395e");
}


void RoundedGraphicsStatus::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setBrush(m_shadowColor);
    painter.drawRoundedRect(rect(), 10, 10);
    drawMainRectangle(&painter, rect());

    painter.drawPixmap(0,0, m_statusMap.value(m_powerStatus));
    painter.drawPixmap(width()/100*48,0, m_statusMap.value(m_signalStatus));
    painter.drawPixmap(0,height()/100*48, m_statusMap.value(m_tempStatus));
    painter.drawPixmap(width()/100*48,height()/100*48, m_statusMap.value(m_fanStatus));
}

void RoundedGraphicsStatus::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int sizeIcon = width()/100*50;

    if(x > 0 && x < sizeIcon && y > 0 && y < sizeIcon)
    {
        if(m_powerStatus == CondeiStatus::Power_on)
        {
            m_powerStatus = CondeiStatus::Power_off;
            emit ChangePower(false);
            update();
            return;
        }
        else
        {
            m_powerStatus = CondeiStatus::Power_on;
            emit ChangePower(true);
            update();
        }
    }
    if(x > sizeIcon && x < width() && y > sizeIcon && y < height())
    {
        if(Settings::instance().readSetting("theme")=="light")
        {
            if(m_fanStatus == CondeiStatus::Black_fan_on)
            {
                m_fanStatus = CondeiStatus::Black_fan_off;
                emit ChangeFan(false);
                update();
                return;
            }
            else
            {
                m_fanStatus = CondeiStatus::Black_fan_on;
                emit ChangeFan(true);
                update();
                return;
            }
            return;
        }

        if(Settings::instance().readSetting("theme")=="dark")
        {
            if(m_fanStatus == CondeiStatus::White_fan_on)
            {
                m_fanStatus = CondeiStatus::White_fan_off;
                emit ChangeFan(false);
                update();
                return;
            }
            else
            {
                m_fanStatus = CondeiStatus::White_fan_on;
                emit ChangeFan(true);
                update();
            }
            return;
        }
    }
}

void RoundedGraphicsStatus::CreateStatusMap()
{
    QPixmap spriteSheet(":/img/img/status.png");

    m_statusMap.insert(CondeiStatus::Power_on,spriteSheet.copy(0,0,180,180));
    m_statusMap.insert(CondeiStatus::Power_off,spriteSheet.copy(180,0,180,180));

    m_statusMap.insert(CondeiStatus::Signal_3,spriteSheet.copy(360,0,180,180));
    m_statusMap.insert(CondeiStatus::Signal_2,spriteSheet.copy(540,0,180,180));
    m_statusMap.insert(CondeiStatus::Signal_1,spriteSheet.copy(720,0,180,180));
    m_statusMap.insert(CondeiStatus::Signal_0,spriteSheet.copy(900,0,180,180));

    m_statusMap.insert(CondeiStatus::Temp_low,spriteSheet.copy(1080,0,180,180));
    m_statusMap.insert(CondeiStatus::Temp_mid,spriteSheet.copy(1260,0,180,180));
    m_statusMap.insert(CondeiStatus::Temp_high,spriteSheet.copy(1440,0,180,180));

    m_statusMap.insert(CondeiStatus::Black_fan_on,spriteSheet.copy(0,180,180,180));
    m_statusMap.insert(CondeiStatus::Black_fan_off,spriteSheet.copy(180,180,180,180));
    m_statusMap.insert(CondeiStatus::White_fan_on,spriteSheet.copy(360,180,180,180));
    m_statusMap.insert(CondeiStatus::White_fan_off,spriteSheet.copy(540,180,180,180));

    m_powerStatus = CondeiStatus::Power_off;
    m_signalStatus = CondeiStatus::Signal_3;
    m_tempStatus = CondeiStatus::Temp_low;
    m_fanStatus = CondeiStatus::White_fan_off;
}

void RoundedGraphicsStatus::GetTempOfSystem(temperatureOfSystem temp)
{
    if(temp == temperatureOfSystem::t_low)
    {
        m_tempStatus = CondeiStatus::Temp_low;
    }
    else if (temp == temperatureOfSystem::t_mid)
    {
        m_tempStatus = CondeiStatus::Temp_mid;
    }
    else
    {
        m_tempStatus = CondeiStatus::Temp_high;
    }
    update();
}

void RoundedGraphicsStatus::GetPowerOfSignal(powerSignal signal)
{
    if(signal == powerSignal::s_none)
    {
        m_signalStatus = CondeiStatus::Signal_0;
    }
    else if (signal == powerSignal::s_low)
    {
        m_signalStatus = CondeiStatus::Signal_1;
    }
    else if (signal == powerSignal::s_mid)
    {
        m_signalStatus = CondeiStatus::Signal_2;
    }
    else
    {
        m_signalStatus = CondeiStatus::Signal_3;
    }
    update();
}

void RoundedGraphicsStatus::getTheme()
{
    if (Settings::instance().readSetting("theme") == "dark")
    {
        m_mainColor = QColor(Settings::instance().readSetting("darkBackgroundColor", ""));
        m_shadowColor = QColor(Settings::instance().readSetting("darkShadowColor", ""));
    }
    else
    {
        m_mainColor = QColor(Settings::instance().readSetting("lightBackgroundColor", ""));
        m_shadowColor = QColor(Settings::instance().readSetting("lightShadowColor", ""));
    }

    if(Settings::instance().readSetting("theme")=="light")
    {
        if(m_fanStatus == CondeiStatus::Black_fan_on)
        {
            m_fanStatus = CondeiStatus::White_fan_on;
            update();
            return;
        }
        else
        {
            m_fanStatus = CondeiStatus::Black_fan_off;
            update();
            return;
        }
        return;
    }

    if(Settings::instance().readSetting("theme")=="dark")
    {
        if(m_fanStatus == CondeiStatus::White_fan_on)
        {
            m_fanStatus = CondeiStatus::White_fan_on;
            update();
            return;
        }
        else
        {
            m_fanStatus = CondeiStatus::White_fan_off;
            emit ChangeFan(true);
            update();
        }
        return;
    }
}
