#include "Settings.h"
#include <QDebug>
Settings::Settings(QObject *parent) : QObject(parent)
{
    m_settings.beginGroup("MyApp");
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
    qDebug() << "Writing setting: " << key << " = " << value;
    m_settings.setValue(key, value);


}

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
        qDebug() << key << " - " << readSetting(key,"");
        xmlWriter.writeTextElement(key, readSetting(key,""));
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

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

void Settings::saveToXml()
{
    saveSettingsToXml();
}
