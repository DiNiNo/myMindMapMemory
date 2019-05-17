#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphicSceneObj = new GrphicScene();
    ui->horizontalLayout->addWidget(graphicSceneObj);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(15);
    pen.setColor(Qt::black);

    for(int i = 0; i < rectangle.size(); ++i){
        painterKnot[i].begin(this);
        painterKnot[i].setRenderHint(QPainter::Antialiasing, true);
        painterKnot[i].scale(0.1, 0.1);
        painterKnot[i].setPen(pen);
        painterKnot[i].drawEllipse(rectangle[i]);
        painterKnot[i].end();
    }

    for(int i = 0; i < path.size(); ++i){
        painterBezier[i].begin(this);
        painterBezier[i].setRenderHint(QPainter::Antialiasing, true);
        painterBezier[i].scale(0.1, 0.1);
        painterBezier[i].setPen(pen);
        painterBezier[i].drawPath(path[i]);
        painterBezier[i].end();
    }
}



void MainWindow::on_cloud_action_triggered()
{
    graphicSceneObj->drawingOutOfOut();
}
