#include "RoundedSettingsWidget.h"
#include "RoundedGraphics.h"
#include "QLabel"

RoundedSettingsWidget::RoundedSettingsWidget(int width, int height, QWidget* parent):RoundedGraphics(width, height, parent)
{
    CreateElements(width, height);
}

void RoundedSettingsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setBrush(m_color);
    painter.drawRoundedRect(rect(), 10, 10);
    drawShadow(&painter, rect());
}

void RoundedSettingsWidget::CreateElements(int width, int height)
{
    QFont headerFont = QFont("Arial",30);
    headerFont.setBold(true);

    QFont textFont = QFont("Arial",20);
    textFont.setBold(true);

    QLabel *tempLabel = new QLabel("Settings", this);
    QLabel *tempGraduate = new QLabel("Temperature graduate", this);
    QLabel *presureGraduate = new QLabel("Pressure graduate", this);
    QLabel *themeLabel = new QLabel("Theme",this);

    int buttonWidth = width / 100 * 25;
    int buttonHeight = height / 100 * 10;
    int spacing = width / 100 * 7;

    tempLabel->setFont(headerFont);
    tempLabel->setAlignment(Qt::AlignCenter);
    tempLabel->setStyleSheet("color: white;");

    tempGraduate->setFont(textFont);
    tempGraduate->setAlignment(Qt::AlignCenter);
    tempGraduate->setStyleSheet("color: white;");

    presureGraduate->setFont(textFont);
    presureGraduate->setAlignment(Qt::AlignCenter);
    presureGraduate->setStyleSheet("color: white;");

    themeLabel->setFont(textFont);
    themeLabel->setAlignment(Qt::AlignCenter);
    themeLabel->setStyleSheet("color: white;");

    int labelWidth = width - width/100*5;
    int labelHeight = 50;
    int x = (width - labelWidth) / 2;

    tempLabel->setGeometry(x, height/100*5, labelWidth, labelHeight);
    tempGraduate->setGeometry(x,height/100*20, labelWidth,labelHeight);
    presureGraduate->setGeometry(x,height/100*45, labelWidth,labelHeight);
    themeLabel->setGeometry(x,height/100*70, labelWidth,labelHeight);

    m_color = QColor("#31395e");


    m_buttonCelsie.setText("C");
    m_buttonFarhengeit.setText("F");
    m_buttonKelvin.setText("K");
    m_buttonMM.setText("Hg");
    m_buttonPascal.setText("P");
    m_buttonDark.setText("Dark");
    m_buttonLigt.setText("Light");
    m_buttonSave.setText("Save");

    m_buttonCelsie.setFont(headerFont);
    m_buttonFarhengeit.setFont(headerFont);
    m_buttonKelvin.setFont(headerFont);
    m_buttonMM.setFont(headerFont);
    m_buttonPascal.setFont(headerFont);
    m_buttonDark.setFont(headerFont);
    m_buttonLigt.setFont(headerFont);
    m_buttonSave.setFont(headerFont);

    m_buttonCelsie.setParent(this);
    m_buttonFarhengeit.setParent(this);
    m_buttonKelvin.setParent(this);
    m_buttonMM.setParent(this);
    m_buttonPascal.setParent(this);
    m_buttonDark.setParent(this);
    m_buttonLigt.setParent(this);
    m_buttonSave.setParent(this);

    m_buttonCelsie.setGeometry(spacing, height/100*30, buttonWidth, buttonHeight);
    m_buttonFarhengeit.setGeometry(2 * spacing + buttonWidth, height/100*30, buttonWidth, buttonHeight);
    m_buttonKelvin.setGeometry(3 * spacing + 2 * buttonWidth, height/100*30, buttonWidth, buttonHeight);

    m_buttonPascal.setGeometry(spacing, height/100*55, buttonWidth, buttonHeight);
    m_buttonMM.setGeometry(2*spacing + buttonWidth, height/100*55, buttonWidth, buttonHeight);

    m_buttonLigt.setGeometry(spacing, height/100*80, buttonWidth, buttonHeight);
    m_buttonDark.setGeometry(2*spacing + buttonWidth, height/100*80, buttonWidth, buttonHeight);

    m_buttonSave.setGeometry(width/100*5,height-buttonHeight*1.05,width-width/100*10,buttonHeight);

    QObject::connect(&m_buttonSave, &QPushButton::clicked, this, &RoundedSettingsWidget::saveButtonClicked);
}

void RoundedSettingsWidget::saveButtonClicked()
{
    this->hide();
}
