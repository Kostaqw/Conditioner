#include "SendData.h"

SendData::SendData(bool isPower, bool fan, powerSignal signal, temperatureOfSystem tempSystem, float temperature, float pressure, float angle, float humidity)
    : m_isPower(isPower), m_fan(fan), m_signal(signal), m_temperatureOfSystem(tempSystem), m_temperature(temperature), m_pressure(pressure), m_angle(angle), m_humidity(humidity)
{
    m_isPower = isPower;
    m_fan = fan;
    m_signal = signal;
    m_temperatureOfSystem = tempSystem;
    m_temperature = temperature;
    m_pressure = pressure;
    m_angle = angle;
    m_humidity = humidity;
}
