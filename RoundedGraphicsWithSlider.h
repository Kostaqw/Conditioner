#pragma once

#include "RoundedGraphics.h"
#include <QSlider>
#include <QStyle>
#include "Settings.h"

class RoundedGraphicsWithSlider : public RoundedGraphics
{
    Q_OBJECT
public:
    RoundedGraphicsWithSlider(int width, int height, QWidget* parent = nullptr);


private slots:
    void handleSliderValueChanged(int value);
public slots:
    void setTemp(int value);

private:
    QSlider* m_slider;
signals:
    void sendTemp(float temp);
};
