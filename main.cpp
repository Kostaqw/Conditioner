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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    QGraphicsScene scene;


        RoundedGraphics *widget1 = new RoundedGraphics(1600, 900, QColor("#18213d"));
        RoundedGraphics *widget2 = new RoundedGraphics(200, 100, QColor("#31395e"));
        RoundedGraphicsWithSlider *widget3 = new RoundedGraphicsWithSlider(200,100,widget1);
        RotatingRectWidget *condei = new RotatingRectWidget(200,200);

        widget3->SetColor(QColor("#31395e"));
        widget3->SetHeader("Temperature");



        widget2->SetText("100 \n 200");
        QGraphicsProxyWidget *proxy1 = scene.addWidget(widget1);
        QGraphicsProxyWidget *proxy2 = scene.addWidget(widget2);
        QGraphicsProxyWidget *proxy3 = scene.addWidget(condei);
        QGraphicsProxyWidget *proxy4 = scene.addWidget(widget3);

        proxy1->setPos(0, 0);
        proxy2->setPos(100, 100);
        proxy3->setPos(250,250);
        proxy4->setPos(20,20);

       QMainWindow window;
       window.setCentralWidget(new GraphicsView(&scene, &window));
       window.show();



    return a.exec();
}
