#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    graphicScene = new GraphicScene();
    ui->horizontalLayout->addWidget(graphicScene);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_knotAction_triggered(){
    graphicScene->drawingOutOfOut();
}
