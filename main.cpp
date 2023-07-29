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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    RoundedGraphics *backGroundWidget = new RoundedGraphics(1024, 768, QColor("#18213d"));
    RoundedGraphicsWithSlider *setTemperatureWidget = new RoundedGraphicsWithSlider(400,200,backGroundWidget);
    RotatingRectWidget *condeiWidget = new RotatingRectWidget(400,400);
    RoundedGraphics *valuesWidget = new RoundedGraphics(400, 200, QColor("#31395e"));
    RoundedGraphicsStatus *statusWidget = new RoundedGraphicsStatus(400, 400);

    setTemperatureWidget->SetColor(QColor("#31395e"));
    setTemperatureWidget->SetHeader("Temperature");


    valuesWidget->SetText("100 \n 200");

    statusWidget->SetColor(QColor("#31395e"));

    QGraphicsProxyWidget *backGroundProxy = scene.addWidget(backGroundWidget);
    QGraphicsProxyWidget *setTemperatureProxy = scene.addWidget(setTemperatureWidget);
    QGraphicsProxyWidget *condeiProxy = scene.addWidget(condeiWidget);
    QGraphicsProxyWidget *valueProxy = scene.addWidget(valuesWidget);
    QGraphicsProxyWidget *statusProxy = scene.addWidget(statusWidget);


    backGroundProxy->setPos(0, 0);
    setTemperatureProxy->setPos(20,20);
    condeiProxy->setPos(20,250);
    valueProxy->setPos(460, 20);
    statusProxy->setPos(460,250);


   QMainWindow window;

   window.setCentralWidget(new GraphicsView(&scene, &window));
   window.show();



    return a.exec();
}
