#pragma once

enum class CondeiStatus {
    Power_on,
    Power_off,
    Signal_3,
    Signal_2,
    Signal_1,
    Signal_0,
    Temp_low,
    Temp_mid,
    Temp_high,
    Black_fan_on,
    Black_fan_off,
    White_fan_on,
    White_fan_off,
};

enum class tempType
{
    Cels,
    Fahrenheit,
    Kelvin
};

enum class Pressure
{
    Pascal,
    Mm
};

enum powerSignal
{
    s_none,
    s_low,
    s_mid,
    s_high
};

enum temperatureOfSystem
{
    t_low,
    t_mid,
    t_high
};
