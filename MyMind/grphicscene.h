#ifndef GRPHICSCENE_H
#define GRPHICSCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTextEdit>

#include "graphicsceneevent.h"
#include "storagepoints.h"
#include "choicebuild.h"


class GrphicScene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GrphicScene(QWidget *parent = nullptr);

    void drawingOutOfOut();

private slots:
    void slotTimer();

private:
    //QGraphicsScene *scene;
    QGraphicsItemGroup *group;

    QTimer *timer;
    QTimer *timerMouseEvent;

    QVector<QPainterPath> path;
    QVector<QPainterPath> pathText;

    QPen penSelectedKnot;

    GraphicSceneEvent *sceneObj;
    StoragePoints storageObj;
    ChoiceBuild choiceObj;

    int knotCount = 0;
    int curveCount = 0;
    int indexSelectedKnot = 0;

    void resizeEvent(QResizeEvent *event);
    void deleteItemGroup();

    void drawingBezier(int startPos_X, int startPos_Y, int c1_X, int c1_Y, int c2_X, int c2_Y, int endPos_X, int endPos_Y, int cornerEarth, int width, int height);
    void drawingKnot(int startPos_X, int startPos_Y, int width, int height, int cornerEarth);

    void updateCurveBezier();
    void updateChildCurve();
    void updateText();
    void drawing();
};

#endif // GRPHICSCENE_H
