#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTextEdit>

#include "storagepoints.h"
#include "choicebuild.h"
#include "graphicsceneevent.h"


class GraphicScene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicScene(QWidget *parent = nullptr);

    void drawingOutOfOut();

private slots:
    void slotTimer();

private:
    QGraphicsItemGroup *group;

    QTimer *timer;
    QTimer *timerMouseEvent;

    QVector<QPainterPath> pathCurve;
    QVector<QPainterPath> pathText;

    QPen penSelectedKnot;

    StoragePoints storagePoints;
    ChoiceBuild choiceBuild;
    GraphicSceneEvent *sceneObj;

    int knotCount = 0;
    int curveCount = 0;
    int indexSelectedKnot = 0;

    void resizeEvent(QResizeEvent *event);
    void deleteItemGroup();

    void drawingBezier(int startPosX, int startPosY, int endPosX, int endPosY, int cornerEarth, int width, int height);
    void drawingKnot(int startPosX, int startPosY, int width, int height, int cornerEarth);

    void updateCurveBezier();
    void updateChildCurve();
    void updateText();
    void drawing();

    QVector<int> calculationCPoints(int c1X, int c1Y, int c2X, int c2Y, int width, int height, int cornerEarth);
};

#endif // GRAPHICSCENE_H
