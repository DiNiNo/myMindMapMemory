#ifndef GRAPHICSCENEEVENT_H
#define GRAPHICSCENEEVENT_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "storagepoints.h"


class GraphicSceneEvent : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphicSceneEvent(QObject *parent = nullptr);

    void setMoveStatusFlag(bool value);

    int getSelectedKnot();

    bool getSelectedStatusFlag();
    bool getMoveStatusFlag();

    void clearText();
    void setTextBackFlag();

    QString getText();
    bool getTextFlag();
    bool getTextBackFlag();

private:
    StoragePoints storageObj;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void selectedKnot(int x, int y);

    int indexSelectedKnot = 0;

    bool selectedStatusFlag = false;
    bool moveStatusFlag = false;

    QString text = "";
    bool textFlag = false;
    bool textBackFlag = false;
};

#endif // GRAPHICSCENEEVENT_H
