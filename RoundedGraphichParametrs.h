#pragma once

#include "Settings.h"
#include "RoundedGraphics.h"
#include "QLabel"
class RoundedGraphichParametrs : public RoundedGraphics
{
public:
    RoundedGraphichParametrs(int width, int height, QWidget* parent = nullptr);
private:
    int m_temp_c;
    int m_temp_f;
    int m_temp_k;

    int m_pres_p;
    int m_pres_mm;

    int m_hum;
    int m_angle;

    QLabel *m_tempLabel;
    QLabel *m_pressureLabel;
    QLabel *m_humidityLabel;
    QLabel *m_angleLabel;

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
     void getAngle(int value);
     void getParametrs(int temp, int pressure, int humidity, int angle);
     void updateWidget();
};
