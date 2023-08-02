#pragma once

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings& instance();
    QString readSetting(const QString& key, const QString& defaultValue = "") const;
    void writeSetting(const QString& key, const QString& value);

private:
    explicit Settings(QObject *parent = nullptr);
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QSettings m_settings;
};

