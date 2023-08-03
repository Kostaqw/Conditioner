#include "Device.h"
#include <QtWidgets>
#include <QFont>
#include <QRandomGenerator>
#include <QMap>

Device::Device(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(512,384);
    setMinimumSize(300,300);
    resize(512,384);

    QFont headerFont("Arial", 18);
    QGridLayout* gridLayout = new QGridLayout();

    m_angleLabel = new QLabel("<: " );
    m_angleLabel->setFont(headerFont);

    m_tempLabel = new QLabel("T: ");
    m_tempLabel->setFont(headerFont);

    m_pressureLabel = new QLabel("P: " + QString::number(QRandomGenerator::global()->bounded(700,800)));
    m_pressureLabel->setFont(headerFont);

    m_humidityLabel = new QLabel("H: " + QString::number(QRandomGenerator::global()->bounded(5,95)));
    m_humidityLabel->setFont(headerFont);

    m_headerLabel = new QLabel("Set values");
    m_headerLabel->setAlignment(Qt::AlignCenter);
    m_headerLabel->setFont(headerFont);

    gridLayout->addWidget(m_tempLabel, 0,0,1,2);
    gridLayout->addWidget(m_pressureLabel, 0,2,1,2);
    gridLayout->addWidget(m_humidityLabel, 1,0,1,2);
    gridLayout->addWidget(m_angleLabel, 1,2,1,2);
    gridLayout->addWidget(m_headerLabel,2,0,1,4);

    m_setAngleLabel = new QLabel("<: ");
    m_setAngleLabel->setFont(headerFont);

    m_setTempLabel = new QLabel("T: ");
    m_setTempLabel->setFont(headerFont);

    m_setPressureLabel = new QLabel("P: ");
    m_setPressureLabel->setFont(headerFont);

    m_setHumidityLabel = new QLabel("H: ");
    m_setHumidityLabel->setFont(headerFont);

    m_tempEdit = new QLineEdit();
    m_pressureEdit = new QLineEdit();
    m_HumidityEdit = new QLineEdit();
    m_AngleEdit = new QLineEdit();

    gridLayout->addWidget(m_setTempLabel, 3,0);
    gridLayout->addWidget(m_tempEdit,3,1);
    gridLayout->addWidget(m_setPressureLabel, 3,2);
    gridLayout->addWidget(m_pressureEdit,3,3);
    gridLayout->addWidget(m_setHumidityLabel, 4,0);
    gridLayout->addWidget(m_HumidityEdit,4,1);
    gridLayout->addWidget(m_setAngleLabel, 4,2);
    gridLayout->addWidget(m_AngleEdit,4,3);

    m_firstBlockLabel = new QLabel("First block");
    m_firstBlockLabel->setFont(headerFont);
    m_secondBlockLabel = new QLabel("Second block");
    m_secondBlockLabel->setFont(headerFont);
    m_thirdBlockLabel = new QLabel("Third block");
    m_thirdBlockLabel->setFont(headerFont);
    m_fourBlackLabel = new QLabel("Four block");
    m_fourBlackLabel->setFont(headerFont);

    gridLayout->addWidget(m_firstBlockLabel,5,0,1,2);
    gridLayout->addWidget(m_secondBlockLabel,5,2,1,2);
    gridLayout->addWidget(m_thirdBlockLabel,7,0,1,2);
    gridLayout->addWidget(m_fourBlackLabel,7,2,1,2);

    m_stateFirstBlock = new QComboBox();
    m_stateFirstBlock->addItem("Power_on");
    m_stateFirstBlock->addItem("Power_off");
    m_stateSecondBlock = new QComboBox();
    m_stateSecondBlock->addItem(signalToString(powerSignal::s_high));
    m_stateSecondBlock->addItem(signalToString(powerSignal::s_mid));
    m_stateSecondBlock->addItem(signalToString(powerSignal::s_low));
    m_stateSecondBlock->addItem(signalToString(powerSignal::s_none));
    m_stateThirdBlock = new QComboBox();
    m_stateThirdBlock->addItem("fan_on");
    m_stateThirdBlock->addItem("fan_off");
    m_stateFourBlock = new QComboBox();
    m_stateFourBlock->addItem(temperatureToString(temperatureOfSystem::t_low));
    m_stateFourBlock->addItem(temperatureToString(temperatureOfSystem::t_mid));
    m_stateFourBlock->addItem(temperatureToString(temperatureOfSystem::t_high));

    gridLayout->addWidget(m_stateFirstBlock,6,0,1,2);
    gridLayout->addWidget(m_stateSecondBlock,6,2,1,2);
    gridLayout->addWidget(m_stateThirdBlock,8,0,1,2);
    gridLayout->addWidget(m_stateFourBlock,8,2,1,2);

    m_sendButton = new QPushButton("Sent");
    gridLayout->addWidget(m_sendButton,9,0,1,4);
    setLayout(gridLayout);

    QObject::connect(m_sendButton, &QPushButton::clicked, [=]()
    {
        emit sendTempOfSystem(stringToTemperature(m_stateFourBlock->currentText()));
        emit sendPowerSignal(stringToPowerSignal(m_stateSecondBlock->currentText()));

        bool p1,p2,p3,p4;
        int temp = m_tempEdit->text().toInt(&p1);
        int press = m_pressureEdit->text().toInt(&p2);
        int humm = m_HumidityEdit->text().toInt(&p3);
        int angle = m_AngleEdit->text().toInt(&p4);

        if(p1 && p2 && p3 && p4)
        {
            m_tempLabel->setText("T: " + QString::number(temp));
            m_pressureLabel->setText("P: " + QString::number(press));
            m_humidityLabel->setText("H: "+QString::number(humm));
            m_angleLabel->setText("<: "+QString::number(angle));
            emit sendParametrs(temp, press, humm, angle);
        }
    });
}

temperatureOfSystem Device::stringToTemperature(const QString &value)
{
    static const QMap<QString, temperatureOfSystem> stringToEnumMap {
            {"low", temperatureOfSystem::t_low},
            {"mid", temperatureOfSystem::t_mid},
            {"high", temperatureOfSystem::t_high}
        };
        return stringToEnumMap.value(value, temperatureOfSystem::t_low);
}
powerSignal Device::stringToPowerSignal(const QString &value)
{
    static const QMap<QString, powerSignal> stringToEnumMap {
            {"3", powerSignal::s_high},
            {"2", powerSignal::s_mid},
            {"1", powerSignal::s_low},
            {"0", powerSignal::s_none}
        };
        return stringToEnumMap.value(value, powerSignal::s_none);
}

QString Device::signalToString(powerSignal value) {
    static const QMap<powerSignal, QString> enumToStringMap {
        {powerSignal::s_high, "3"},
        {powerSignal::s_mid, "2"},
        {powerSignal::s_low, "1"},
        {powerSignal::s_none, "0"}
    };
    return enumToStringMap.value(value, QString());
}
QString Device::temperatureToString(temperatureOfSystem value) {
    static const QMap<temperatureOfSystem, QString> enumToStringMap {
        {temperatureOfSystem::t_low, "low"},
        {temperatureOfSystem::t_mid, "mid"},
        {temperatureOfSystem::t_high, "high" }
    };
    return enumToStringMap.value(value, QString());
}
/*
void Device::receiveData(SendData data)
{


    m_pressureLabel->setText("P: " + QString::number(data.m_pressure));



    if(data.m_signal == powerSignal::s_high)
    {
        m_stateSecondBlock->setCurrentIndex(0);
    }
    else if(data.m_signal == powerSignal::s_mid)
    {
        m_stateSecondBlock->setCurrentIndex(1);
    }
    else if(data.m_signal == powerSignal::s_low)
    {
        m_stateSecondBlock->setCurrentIndex(2);
    }
    else
    {
        m_stateSecondBlock->setCurrentIndex(3);
    }




    if(data.m_temperatureOfSystem == temperatureOfSystem::t_high)
    {
        m_stateFourBlock->setCurrentIndex(0);
    }
    else if(data.m_temperatureOfSystem == temperatureOfSystem::t_mid)
    {
        m_stateFourBlock->setCurrentIndex(1);
    }
    else
    {
        m_stateFourBlock->setCurrentIndex(2);
    }
}*/

void Device::GetTemp(float temp)
{
  m_tempLabel->setText("T: " + QString::number(temp));
}

void Device::GetPowerStatus(bool power)
{
  if(power)
  {
      m_stateFirstBlock->setCurrentIndex(0);
  }
  else
  {
      m_stateFirstBlock->setCurrentIndex(1);
  }
}

void Device::GetFanStatus(bool fan)
{
  if(fan)
  {
      m_stateThirdBlock->setCurrentIndex(0);
  }
  else
  {
      m_stateThirdBlock->setCurrentIndex(1);
  }
}

void Device::GetAngle(int angle)
{
    m_angleLabel->setText("<: " + QString::number(angle));
}
