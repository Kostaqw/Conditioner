#pragma once

#include "StatusEnums.h"
#include <QWidget>

class SendData
{
public:
    SendData(bool isPower, bool fan, powerSignal signal, temperatureOfSystem tempSystem, float temperature, float pressure, float angle, float humidity);

    bool m_isPower;
    bool m_fan;
    powerSignal m_signal;
    temperatureOfSystem m_temperatureOfSystem;

    float m_temperature;
    float m_pressure;
    float m_angle;
    float m_humidity;

signals:
  void sendParametrs(float temp, float pressure, float amgle, float humidity);
  void sendStatus(bool isPower, bool isFan, powerSignal powerSignal, temperatureOfSystem temp);
};

