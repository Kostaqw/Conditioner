#include "CustomSlider.h"

CustomSlider::CustomSlider(Qt::Orientation orientation, QWidget* parent)
    : QSlider(orientation, parent)
{
    setStyleSheet("QSlider { background-color: transparent; }"
                  "QSlider::groove:horizontal {"
                  "border-top: 2px solid #999999;"
                  "border-bottom: 2px solid #999999;"
                  "height: 3px; /* высота полоски */"
                  "background: #dddddd;"
                  "margin: 2px 0;"
                  "}"
                  "QSlider::handle:horizontal {"
                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #7cc7ea, stop:1 #7cc7ea); /* цвет ползунка */"
                  "border: 2px solid #88cded;"
                  "width: 8px; /* ширина ползунка */"
                  "height: 8px; /* высота ползунка */"
                  "margin-top: -5px;"
                  "margin-bottom: -5px;"
                  "border-radius: 5px; /* скругление углов ползунка */"
                  "}");
}
