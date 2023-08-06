#include "Widget.h"
#include "Device.h"
#include <QApplication>
#include "RoundedGraphics.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include "GraphicsView.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QSlider>
#include "CustomSlider.h"
#include "RoundedGraphicsWithSlider.h"
#include "RotatingRectWidget.h"
#include "RoundedGraphicsStatus.h"
#include "RoundedSettingsWidget.h"
#include "RoundedGraphichParametrs.h"
#include "Settings.h"

void createColorsSettings()
{

        Settings::instance().writeSetting("darkBackgroundColor", "#18213d");

        Settings::instance().writeSetting("darkMainColor", "#31395e");


        Settings::instance().writeSetting("lightBackgroundColor", "#F0F0F0");

        Settings::instance().writeSetting("lightMainColor", "#D3D3D3");

        Settings::instance().writeSetting("lightShadowColor", "#A0A0A0");
}

int main(int argc, char *argv[])
{
    createColorsSettings();
    QApplication a(argc, argv);

    Device *dev = new Device();

    QGraphicsScene scene;

    RoundedGraphics *backGroundWidget = new RoundedGraphics(1024, 768, QColor("#18213d"));
    RoundedGraphicsWithSlider *setTemperatureWidget = new RoundedGraphicsWithSlider(400,200,backGroundWidget);
    RotatingRectWidget *condeiWidget = new RotatingRectWidget(400,400);
    RoundedGraphichParametrs *valuesWidget = new RoundedGraphichParametrs(400, 200, NULL);
    RoundedGraphicsStatus *statusWidget = new RoundedGraphicsStatus(400, 400);
    RoundedSettingsWidget *settingsWidget = new RoundedSettingsWidget(400,768);
    QPushButton *settingsButton = new QPushButton("Settings");

    setTemperatureWidget->SetColor(QColor("#31395e"));
    setTemperatureWidget->SetHeader("Temperature");
    settingsWidget->hide();

    statusWidget->SetColor(QColor("#31395e"));

    QGraphicsProxyWidget *backGroundProxy = scene.addWidget(backGroundWidget);
    QGraphicsProxyWidget *setTemperatureProxy = scene.addWidget(setTemperatureWidget);
    QGraphicsProxyWidget *condeiProxy = scene.addWidget(condeiWidget);
    QGraphicsProxyWidget *valueProxy = scene.addWidget(valuesWidget);
    QGraphicsProxyWidget *statusProxy = scene.addWidget(statusWidget);
    QGraphicsProxyWidget *buttonProxy = scene.addWidget(settingsButton);
    QGraphicsProxyWidget *settingsProxy = scene.addWidget(settingsWidget);

    backGroundProxy->setPos(0, 0);
    setTemperatureProxy->setPos(20,20);
    condeiProxy->setPos(20,250);
    valueProxy->setPos(460, 20);
    statusProxy->setPos(460,250);
    buttonProxy->setPos(1024-settingsButton->width(),768-settingsButton->height());
    settingsProxy->setPos(1024-400,0);

   QMainWindow window;

   window.resize(1200,1200);
   window.setCentralWidget(new GraphicsView(&scene, &window));
   window.show();


   dev->show();
   QObject::connect(dev, &Device::sendParametrs, valuesWidget, &RoundedGraphichParametrs::getParametrs);
   QObject::connect(settingsButton, &QPushButton::clicked, [=](){settingsWidget->show();});
   QObject::connect(setTemperatureWidget, &RoundedGraphicsWithSlider::sendTemp, dev, &Device::GetTemp);

   QObject::connect(statusWidget, &RoundedGraphicsStatus::ChangePower, dev, &Device::GetPowerStatus);
   QObject::connect(statusWidget, &RoundedGraphicsStatus::ChangeFan, dev, &Device::GetFanStatus);

   QObject::connect(condeiWidget, &RotatingRectWidget::changeAngle, dev, &Device::GetAngle);
   QObject::connect(condeiWidget, &RotatingRectWidget::changeAngle, valuesWidget, &RoundedGraphichParametrs::getAngle);

   QObject::connect(dev, &Device::sendPowerSignal, statusWidget, &RoundedGraphicsStatus::GetPowerOfSignal);
   QObject::connect(dev, &Device::sendTempOfSystem, statusWidget, &RoundedGraphicsStatus::GetTempOfSystem);
   QObject::connect(dev, &Device::sendParametrs, condeiWidget, [condeiWidget](int temp, int pressure, int humidity, int angle){condeiWidget->getAngle(angle);});

   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, valuesWidget, &RoundedGraphichParametrs::updateWidget);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, backGroundWidget, &RoundedGraphics::getTheme);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, setTemperatureWidget, &RoundedGraphics::getTheme);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, condeiWidget, &RoundedGraphics::getTheme);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, valuesWidget, &RoundedGraphics::getTheme);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, statusWidget, &RoundedGraphics::getTheme);
   QObject::connect(settingsWidget, &RoundedSettingsWidget::changeSettings, settingsWidget, &RoundedGraphics::getTheme);

   QObject::connect(&a, &QCoreApplication::aboutToQuit, &Settings::instance(), &Settings::saveToXml);
   QObject::connect(&Settings::instance(), &Settings::sendButtonStates, settingsWidget, &RoundedSettingsWidget::getButtonState);
   QObject::connect(&Settings::instance(), &Settings::sendSetedTemperature,setTemperatureWidget, &RoundedGraphicsWithSlider::setTemp);

   dev->sendParametrs(QRandomGenerator::global()->bounded(10,30), QRandomGenerator::global()->bounded(1000,2000),QRandomGenerator::global()->bounded(5,95),0);
   Settings::instance().loadSettingsFromXml();

   return a.exec();
}
