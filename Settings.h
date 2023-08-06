#pragma once

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QXmlStreamWriter>

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings& instance();
    QString readSetting(const QString& key, const QString& defaultValue = "") const;
    void writeSetting(const QString& key, const QString& value);

    void saveSettingsToXml();
    void loadSettingsFromXml();

public slots:
    void saveToXml();

private:
    explicit Settings(QObject *parent = nullptr);
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QSettings m_settings;
signals:
    void sendButtonStates(QString temp, QString press, QString theme);
    void sendSetedTemperature(int temp);
};

