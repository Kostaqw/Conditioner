#pragma once

#include "RoundedGraphics.h"

class RoundedGraphichParametrs : public RoundedGraphics
{
public:
    RoundedGraphichParametrs(int width, int height, QWidget* parent = nullptr);
private:
    int m_temp;
    int m_pres;
    int m_hum;
    int m_angle;

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
     void getParametrs(int temp, int pressure, int humidity, int angle);
};

