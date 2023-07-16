#include "Device.h"
#include <QtWidgets>
#include <QFont>

Device::Device(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(512,384);
    setMinimumSize(300,300);
    resize(512,384);

    QFont headerFont("Arial", 18);
    QGridLayout* gridLayout = new QGridLayout();

    m_angleLabel = new QLabel("<: ");
    m_angleLabel->setFont(headerFont);

    m_tempLabel = new QLabel("T: ");
    m_tempLabel->setFont(headerFont);

    m_pressureLabel = new QLabel("P: ");
    m_pressureLabel->setFont(headerFont);

    m_humidityLabel = new QLabel("H: ");
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

    gridLayout->addWidget(m_firstBlockLabel,5,0,1,2);
    gridLayout->addWidget(m_secondBlockLabel,5,2,1,2);
    gridLayout->addWidget(m_thirdBlockLabel,7,0,1,2);

    m_stateFirstBlock = new QComboBox();
    m_stateFirstBlock->addItem("Good");
    m_stateFirstBlock->addItem("middle");
    m_stateFirstBlock->addItem("Bad");
    m_stateSecondBlock = new QComboBox();
    m_stateSecondBlock->addItem("0");
    m_stateSecondBlock->addItem("20");
    m_stateSecondBlock->addItem("40");
    m_stateSecondBlock->addItem("60");
    m_stateSecondBlock->addItem("80");
    m_stateSecondBlock->addItem("100");
    m_stateThirdBlock = new QComboBox();
    m_stateThirdBlock->addItem("enable");
    m_stateThirdBlock->addItem("disable");

    gridLayout->addWidget(m_stateFirstBlock,6,0,1,2);
    gridLayout->addWidget(m_stateSecondBlock,6,2,1,2);
    gridLayout->addWidget(m_stateThirdBlock,8,0,1,2);

    m_sendButton = new QPushButton("Sent");
    gridLayout->addWidget(m_sendButton,9,0,1,4);
    setLayout(gridLayout);
}

void Device::GetData(QString data)
{}
void Device::SendData(QString data)
{}
