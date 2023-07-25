#pragma once

#include "RoundedGraphics.h"
#include <QSlider>

class RoundedGraphicsWithSlider : public RoundedGraphics
{
    Q_OBJECT
public:
    RoundedGraphicsWithSlider(int width, int height, QWidget* parent = nullptr);

private slots:
    void handleSliderValueChanged(int value);

private:
    QSlider* m_slider;
};
