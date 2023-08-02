#include "Settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    // Инициализация объекта QSettings
    m_settings.beginGroup("MyApp"); // Опционально: можно использовать группы для категоризации настроек
}

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

QString Settings::readSetting(const QString& key, const QString& defaultValue) const
{
    return m_settings.value(key, defaultValue).toString();
}

void Settings::writeSetting(const QString& key, const QString& value)
{
    m_settings.setValue(key, value);
}
