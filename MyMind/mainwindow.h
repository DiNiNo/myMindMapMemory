#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtWidgets>
#include <QResizeEvent>

#include "storagepoints.h"
#include "choicebuild.h"
#include "grphicscene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *widget;

    GrphicScene *graphicSceneObj;
    StoragePoints storageObj;
    ChoiceBuild choiceObj;

    QVector<QPainterPath> path;
    QVector<QRectF> rectangle;

    QPainter* painterBezier = new QPainter[200];
    QPainter* painterKnot = new QPainter[200];

    //int countBezier = 0;
    //int countKnot = 0;

    bool flag = false;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_cloud_action_triggered();
};

#endif // MAINWINDOW_H
