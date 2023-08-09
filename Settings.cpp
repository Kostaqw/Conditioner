#include "Settings.h"

/**
 * @brief Конструктор класса настроек.
 * @param parent Родительский объект.
 */
Settings::Settings(QObject *parent) : QObject(parent)
{
    m_settings.beginGroup("MyApp");
}

/**
 * @brief Получение экземпляра класса настроек.
 * @return Ссылка на экземпляр класса настроек.
 */
Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

/**
 * @brief Чтение настройки по ключу.
 * @param key Ключ настройки.
 * @param defaultValue Значение по умолчанию, если настройка отсутствует.
 * @return Значение настройки.
 */
QString Settings::readSetting(const QString& key, const QString& defaultValue) const
{
    return m_settings.value(key, defaultValue).toString();
}

/**
 * @brief Запись настройки.
 * @param key Ключ настройки.
 * @param value Значение настройки.
 */
void Settings::writeSetting(const QString& key, const QString& value)
{
    m_settings.setValue(key, value);
}

/**
 * @brief Сохранение настроек в XML-файл.
 */
void Settings::saveSettingsToXml()
{
    QFile file("settings");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QStringList allKeys = m_settings.allKeys();

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");

    foreach(const QString& key, allKeys)
    {
        xmlWriter.writeTextElement(key, readSetting(key,""));
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

/**
 * @brief Загрузка настроек из XML-файла.
 */
void Settings::loadSettingsFromXml()
{
    QFile file("settings");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QXmlStreamReader xmlReader(&file);

    QString temp;
    QString pres;
    QString them;
    int setTemp;

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "Settings")
            {
            }
            else
            {
                QString key = xmlReader.name().toString();
                if(key=="temperature")
                {
                    temp = readSetting(key, "C");
                }
                if(key=="pressure")
                {
                    pres = readSetting(key,"P");
                }
                if(key=="theme")
                {
                    them = readSetting(key,"dark");
                }
                if(key == "setTemp")
                {
                    setTemp = readSetting(key,"25").toInt();
                }
            }

        }
    }

    if (xmlReader.hasError())
    {

    }

    file.close();
    emit sendButtonStates(temp, pres, them);
    emit sendSetedTemperature(setTemp);
}

/**
 * @brief Сохранение настроек в XML-файл.
 */
void Settings::saveToXml()
{
    saveSettingsToXml();
}
