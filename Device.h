#pragma once

#include <QWidget>

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

    QLineEdit* m_tempEdit;
    QLineEdit* m_pressureEdit;
    QLineEdit* m_AngleEdit;
    QLineEdit* m_HumidityEdit;

    QComboBox* m_stateFirstBlock;
    QComboBox* m_stateSecondBlock;
    QComboBox* m_stateThirdBlock;

    QPushButton* m_sendButton;

public:
    explicit Device(QWidget *parent = nullptr);

public slots:
    void GetData(QString data);
    void SendData(QString data);

};

