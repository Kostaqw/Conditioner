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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Device *dev = new Device();

    QGraphicsScene scene;

    RoundedGraphics *backGroundWidget = new RoundedGraphics(1024, 768, QColor("#18213d"));
    RoundedGraphicsWithSlider *setTemperatureWidget = new RoundedGraphicsWithSlider(400,200,backGroundWidget);
    RotatingRectWidget *condeiWidget = new RotatingRectWidget(400,400);
    RoundedGraphics *valuesWidget = new RoundedGraphics(400, 200, QColor("#31395e"));
    RoundedGraphicsStatus *statusWidget = new RoundedGraphicsStatus(400, 400);
    RoundedSettingsWidget *settingsWidget = new RoundedSettingsWidget(400,768);
    QPushButton *settingsButton = new QPushButton("Settings");

    setTemperatureWidget->SetColor(QColor("#31395e"));
    setTemperatureWidget->SetHeader("Temperature");
    settingsWidget->hide();

    valuesWidget->SetText("100 \n 200");

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

   window.setCentralWidget(new GraphicsView(&scene, &window));
   window.show();

    dev->show();
   QObject::connect(settingsButton, &QPushButton::clicked, [=](){settingsWidget->show();});
   QObject::connect(setTemperatureWidget, &RoundedGraphicsWithSlider::sendTemp, dev, &Device::GetTemp);
   QObject::connect(statusWidget, &RoundedGraphicsStatus::ChangePower, dev, &Device::GetPowerStatus);
   QObject::connect(statusWidget, &RoundedGraphicsStatus::ChangeFan, dev, &Device::GetFanStatus);
   QObject::connect(condeiWidget, &RotatingRectWidget::changeAngle, dev, &Device::GetAngle);
   QObject::connect(dev, &Device::sendPowerSignal, statusWidget, &RoundedGraphicsStatus::GetPowerOfSignal);
   QObject::connect(dev, &Device::sendTempOfSystem, statusWidget, &RoundedGraphicsStatus::GetTempOfSystem);
   return a.exec();
}
