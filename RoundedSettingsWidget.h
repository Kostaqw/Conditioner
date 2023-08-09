#pragma once

#include "Settings.h"
#include "RoundedGraphics.h"
#include "QPushButton"
#include "QLabel"
#include "RoundedGraphics.h"
#include "QLabel"

class RoundedSettingsWidget : public RoundedGraphics
{
  Q_OBJECT
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


     QLabel *m_tempLabel;
     QLabel *m_tempGraduate;
     QLabel *m_presureGraduate;
     QLabel *m_themeLabel;


    void CreateElements(int width, int height);

signals:
    void changeSettings();

public slots:
    void UpdatePainter();
    void getButtonState(QString temp, QString pressure, QString theme);
    void startApp();

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
