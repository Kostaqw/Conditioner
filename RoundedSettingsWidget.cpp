#include "RoundedSettingsWidget.h"
#include "RoundedGraphics.h"
#include "QLabel"

/**
 * @brief Конструктор класса RoundedSettingsWidget.
 * @param width Ширина виджета.
 * @param height Высота виджета.
 * @param parent Родительский виджет.
 */
RoundedSettingsWidget::RoundedSettingsWidget(int width, int height, QWidget* parent):RoundedGraphics(width, height, parent)
{
    CreateElements(width, height);
}

/**
 * @brief Обработчик события отрисовки виджета.
 * @param event Событие отрисовки.
 */
void RoundedSettingsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setBrush(m_shadowColor);
    painter.drawRoundedRect(rect(), 10, 10);
    drawMainRectangle(&painter, rect());
}

/**
 * @brief Создание элементов интерфейса и установка их параметров.
 * @param width Ширина виджета.
 * @param height Высота виджета.
 */
void RoundedSettingsWidget::CreateElements(int width, int height)
{
    QFont headerFont = QFont("Arial",30);
    headerFont.setBold(true);

    QFont textFont = QFont("Arial",20);
    textFont.setBold(true);

    m_tempLabel= new QLabel("Settings", this);
    m_tempGraduate = new QLabel("Temperature graduate", this);
    m_presureGraduate = new QLabel("Pressure graduate", this);
    m_themeLabel = new QLabel("Theme",this);

    int buttonWidth = width / 100 * 25;
    int buttonHeight = height / 100 * 10;
    int spacing = width / 100 * 7;

    m_tempLabel->setFont(headerFont);
    m_tempLabel->setAlignment(Qt::AlignCenter);


    m_tempGraduate->setFont(textFont);
    m_tempGraduate->setAlignment(Qt::AlignCenter);


    m_presureGraduate->setFont(textFont);
    m_presureGraduate->setAlignment(Qt::AlignCenter);


    m_themeLabel->setFont(textFont);
    m_themeLabel->setAlignment(Qt::AlignCenter);



    int labelWidth = width - width/100*5;
    int labelHeight = 50;
    int x = (width - labelWidth) / 2;

    m_tempLabel->setGeometry(x, height/100*5, labelWidth, labelHeight);
    m_tempGraduate->setGeometry(x,height/100*20, labelWidth,labelHeight);
    m_presureGraduate->setGeometry(x,height/100*45, labelWidth,labelHeight);
    m_themeLabel->setGeometry(x,height/100*70, labelWidth,labelHeight);

    m_shadowColor = QColor("#31395e");


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

    m_activeButoonStyle = "QPushButton {"
                          "   background-color: orange;"
                          "   border: none;"
                          "}"
                          "QPushButton:focus {"
                          "   outline: none;"
                          "}";
    m_inActiveButoonStyle = "background-color: white";

    QObject::connect(&m_buttonSave, &QPushButton::clicked, this, &RoundedSettingsWidget::saveButtonClicked);
    QObject::connect(&m_buttonCelsie, &QPushButton::clicked, this, &RoundedSettingsWidget::celstButtonClicked);
    QObject::connect(&m_buttonFarhengeit, &QPushButton::clicked, this, &RoundedSettingsWidget::farhButtonClicked);
    QObject::connect(&m_buttonKelvin, &QPushButton::clicked, this, &RoundedSettingsWidget::kelvButtonClicked);
    QObject::connect(&m_buttonMM, &QPushButton::clicked, this, &RoundedSettingsWidget::hgButtonClicked);
    QObject::connect(&m_buttonPascal, &QPushButton::clicked, this, &RoundedSettingsWidget::pascalButtonClicked);
    QObject::connect(&m_buttonLigt, &QPushButton::clicked, this, &RoundedSettingsWidget::lightButtonClicked);
    QObject::connect(&m_buttonDark, &QPushButton::clicked, this, &RoundedSettingsWidget::darlButtonClicked);
}

/**
 * @brief Обновление отрисовки виджета.
 */
void RoundedSettingsWidget::UpdatePainter()
{
    update();
}

/**
 * @brief Установка состояния кнопок на основе предоставленных значений.
 * @param temp Выбранная единица температуры.
 * @param pressure Выбранная единица давления.
 * @param theme Выбранная тема.
 */
void RoundedSettingsWidget::getButtonState(QString temp, QString pressure, QString theme)
{
    if(temp=="C")
    {
        celstButtonClicked();
    }
    else if(temp=="F")
    {
        farhButtonClicked();
    }
    else
    {
        kelvButtonClicked();
    }

    if(pressure=="P")
    {
        pascalButtonClicked();
    }
    else
    {
        hgButtonClicked();
    }

    if(theme=="dark")
    {
        darlButtonClicked();
    }
    else
    {
        lightButtonClicked();
    }
}

/**
 * @brief Слот: обработка события нажатия кнопки "Save".
 * Изменение цвета текста в зависимости от выбранной темы и отправка сигнала changeSettings.
 */
void RoundedSettingsWidget::saveButtonClicked()
{
    if(Settings::instance().readSetting("theme")=="dark")
    {
        m_tempLabel->setStyleSheet("color: white;");
        m_tempGraduate->setStyleSheet("color: white;");
        m_presureGraduate->setStyleSheet("color: white;");
        m_themeLabel->setStyleSheet("color: white;");
    }
    else
    {
        m_tempLabel->setStyleSheet("color: black;");
        m_tempGraduate->setStyleSheet("color: black;");
        m_presureGraduate->setStyleSheet("color: black;");
        m_themeLabel->setStyleSheet("color: black;");
    }
    emit changeSettings();
    this->hide();
}

/**
 * @brief Слот: обработка события нажатия кнопки выбора шкалы измерения температуры (цльсии).
 */
void RoundedSettingsWidget::celstButtonClicked()
{
    m_buttonCelsie.setStyleSheet(m_activeButoonStyle);
    m_buttonFarhengeit.setStyleSheet(m_inActiveButoonStyle);
    m_buttonKelvin.setStyleSheet(m_inActiveButoonStyle);
    Settings::instance().writeSetting("temperature", "C");

}

/**
 * @brief Слот: обработка события нажатия кнопки выбора шкалы измерения температуры (фаренгейт).
 */
void RoundedSettingsWidget::farhButtonClicked()
{
    m_buttonCelsie.setStyleSheet(m_inActiveButoonStyle);
    m_buttonFarhengeit.setStyleSheet(m_activeButoonStyle);
    m_buttonKelvin.setStyleSheet(m_inActiveButoonStyle);
    Settings::instance().writeSetting("temperature", "F");
}

/**
 * @brief Слот: обработка события нажатия кнопки выбора шкалы измерения температуры (кельвин).
 */
void RoundedSettingsWidget::kelvButtonClicked()
{
    m_buttonCelsie.setStyleSheet(m_inActiveButoonStyle);
    m_buttonFarhengeit.setStyleSheet(m_inActiveButoonStyle);
    m_buttonKelvin.setStyleSheet(m_activeButoonStyle);
    Settings::instance().writeSetting("temperature", "K");
}

/**
 * @brief Слот: обработка события нажатия кнопки выбора давления (Паскали).
 */
void RoundedSettingsWidget::pascalButtonClicked()
{
    m_buttonPascal.setStyleSheet(m_activeButoonStyle);
    m_buttonMM.setStyleSheet(m_inActiveButoonStyle);
    Settings::instance().writeSetting("pressure", "P");

}

/**
 * @brief Слот: обработка события нажатия кнопки выбора давления (мм. рт. ст.).
 */
void RoundedSettingsWidget::hgButtonClicked()
{
    m_buttonPascal.setStyleSheet(m_inActiveButoonStyle);
    m_buttonMM.setStyleSheet(m_activeButoonStyle);
    Settings::instance().writeSetting("pressure", "Mm");
}

/**
 * @brief Слот: обработка события нажатия кнопки выбора светлой темы.
 */
void RoundedSettingsWidget::lightButtonClicked()
{
    m_buttonLigt.setStyleSheet(m_activeButoonStyle);
    m_buttonDark.setStyleSheet(m_inActiveButoonStyle);
    Settings::instance().writeSetting("theme", "light");
}

/**
 * @brief Слот: обработка события нажатия кнопки выбора темной темы.
 */
void RoundedSettingsWidget::darlButtonClicked()
{
    m_buttonLigt.setStyleSheet(m_inActiveButoonStyle);
    m_buttonDark.setStyleSheet(m_activeButoonStyle);
    Settings::instance().writeSetting("theme", "dark");
}

/**
 * @brief Слот при запуске приложения.
 */
void RoundedSettingsWidget::startApp()
{
    saveButtonClicked();
}
