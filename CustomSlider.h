#pragma once


#include <QtWidgets>

class CustomSlider : public QSlider
{
public:
    explicit CustomSlider(Qt::Orientation orientation, QWidget* parent = nullptr);
};
