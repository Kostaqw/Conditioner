#include "RoundedGraphics.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include "Settings.h"
#include "QDebug"
#include "Settings.h"

RoundedGraphics::RoundedGraphics(int width, int height, QWidget *parent) : QWidget(parent), m_width(width), m_height(height)
{
    setFixedSize(width, height);
    setAttribute(Qt::WA_TranslucentBackground);
    m_headerFont = QFont("Arial", 40);
    m_headerFont.setBold(true);

    m_textFont = QFont("Arial", 40);
    m_textFont.setBold(true);
}

RoundedGraphics::RoundedGraphics(int width, int height, const QColor& color, QWidget *parent) :
    QWidget(parent), m_width(width), m_height(height), m_shadowColor(color)
{
    setFixedSize(m_width, m_height);
    setAttribute(Qt::WA_TranslucentBackground);

    m_headerFont = QFont("Arial", 40);
    m_headerFont.setBold(true);

    m_textFont = QFont("Arial", 40);
    m_textFont.setBold(true);
}

void RoundedGraphics :: paintEvent(QPaintEvent *event)
{

   Q_UNUSED(event);
   QPainter painter(this);

   painter.setRenderHint(QPainter::Antialiasing);

   painter.setPen(Qt::NoPen);
   painter.setBrush(m_shadowColor);
   painter.drawRoundedRect(rect(), 10, 10);
   drawMainRectangle(&painter, rect());



   if(m_isHeader)
   {
       painter.setFont(m_headerFont);

       QFontMetrics fm(m_headerFont);
       int textWidth = fm.width(m_header);
       int textHeight = fm.height();

       int x = (width() - textWidth) / 2;
       int y = textHeight;

       if(Settings::instance().readSetting("theme")=="dark")
       {
        painter.setPen(Qt::white);
       }
       else
       {
        painter.setPen(Qt::black);
       }
       painter.drawText(x, y, m_header);
   }

   if(m_text != nullptr)
   {
       painter.setFont(m_textFont);
       QRect textRect = QRect(0, 0, width(), height());
       QTextOption textOption;
       textOption.setAlignment(Qt::AlignCenter);
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
}

void RoundedGraphics::SetText(QString text)
{
    m_text = text;
}
void RoundedGraphics::SetText(qreal value)
{
    m_text =  QString::number(value);
}
void RoundedGraphics::SetColor(QColor color)
{
    m_mainColor = color;
}
void RoundedGraphics::SetColor(QColor color, QColor shadow)
{
    m_shadowColor = shadow;
    m_mainColor = color;
}
void RoundedGraphics::SetHeader(QString header)
{
    m_header = header;
    m_isHeader = true;
}
void RoundedGraphics::SetHeaderFont(QFont *headerFont)
{

    m_headerFont = *headerFont;
}
void RoundedGraphics::SetTextFont(QFont *textFont)
{
    m_textFont = *textFont;
}
void RoundedGraphics::drawMainRectangle(QPainter* painter, const QRect& rect)
{
    if (!m_mainColor.isValid())
    {
        m_mainColor = QColor(0, 0, 0, 100);
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_mainColor);
    painter->drawRoundedRect(rect.adjusted(5, 5, -5, -5), 10, 10);
}



RoundedGraphics::~RoundedGraphics()
{

}

void RoundedGraphics::getTheme()
{


    if (Settings::instance().readSetting("theme") == "dark")
    {
        qDebug() << "set dark theme maincolor = " << Settings::instance().readSetting("darkMainColor", "") << " shadowColor = " << Settings::instance().readSetting("darkShadowColor", "");
        m_mainColor = QColor(Settings::instance().readSetting("darkBackgroundColor", ""));
        m_shadowColor = QColor(Settings::instance().readSetting("darkShadowColor", ""));
    }
    else
    {
        qDebug() << "set light theme maincolor = " << Settings::instance().readSetting("lightBackgroundColor", "") << " shadowColor = " << Settings::instance().readSetting("lightShadowColor", "");
        m_mainColor = QColor(Settings::instance().readSetting("lightBackgroundColor", ""));
        m_shadowColor = QColor(Settings::instance().readSetting("lightShadowColor", ""));
    }
    update();
}
