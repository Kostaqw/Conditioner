#pragma once

#include "RoundedGraphics.h"
#include "QPushButton"
class RoundedSettingsWidget : public RoundedGraphics
{
public:
    RoundedSettingsWidget(int width, int height, QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_activeButoonStyle;
    QString m_inActiveButoonStyle;

    QPushButton m_buttonCelsie;
    QPushButton m_buttonFarhengeit;
    QPushButton m_buttonKelvin;

    QPushButton m_buttonPascal;
    QPushButton m_buttonMM;

    QPushButton m_buttonLigt;
    QPushButton m_buttonDark;

    QPushButton m_buttonSave;

    QFont m_textFont;

    void CreateElements(int width, int height);

private slots:
    void saveButtonClicked();
    void celstButtonClicked();
    void farhButtonClicked();
    void kelvButtonClicked();
    void pascalButtonClicked();
    void hgButtonClicked();
    void lightButtonClicked();
    void darlButtonClicked();
};

