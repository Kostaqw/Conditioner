#pragma once

#include <QWidget>
#include "SendData.h"
#include <QtGlobal>

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;

class Device : public QWidget
{
    Q_OBJECT
private:

    QLabel* m_tempLabel;
    QLabel* m_pressureLabel;
    QLabel* m_angleLabel;
    QLabel* m_humidityLabel;

    QLabel* m_headerLabel;

    QLabel* m_setTempLabel;
    QLabel* m_setPressureLabel;
    QLabel* m_setAngleLabel;
    QLabel* m_setHumidityLabel;

    QLabel* m_firstBlockLabel;
    QLabel* m_secondBlockLabel;
    QLabel* m_thirdBlockLabel;
    QLabel* m_fourBlackLabel;

    QLineEdit* m_tempEdit;
    QLineEdit* m_pressureEdit;
    QLineEdit* m_AngleEdit;
    QLineEdit* m_HumidityEdit;

    QComboBox* m_stateFirstBlock;
    QComboBox* m_stateSecondBlock;
    QComboBox* m_stateThirdBlock;
    QComboBox* m_stateFourBlock;

    QPushButton* m_sendButton;

    temperatureOfSystem stringToTemperature(const QString &value);
    powerSignal stringToPowerSignal(const QString &value);
    QString temperatureToString(temperatureOfSystem value);
    QString signalToString(powerSignal value);

public:
    explicit Device(QWidget *parent = nullptr);

signals:
    void sendData(SendData data);
    void sendTempOfSystem(temperatureOfSystem temp);
    void sendPowerSignal(powerSignal signal);
    void sendParametrs(int temp, int pressure, int humidity, int angle);

public slots:
    void GetTemp(float Temp);
    void GetPowerStatus(bool power);
    void GetFanStatus(bool fan);
    void GetAngle(int angle);
};

