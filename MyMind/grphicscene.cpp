#include "grphicscene.h"
#include <iostream>

GrphicScene::GrphicScene(QWidget *parent):QGraphicsView (parent){
    this->setMinimumSize(100, 100);

    QGraphicsView::setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);

    sceneObj = new GraphicSceneEvent();
    this->setScene(sceneObj);
    sceneObj->setSceneRect(0, 0, 30000, 30000);

    group = new QGraphicsItemGroup();

    sceneObj->addItem(group);

    QGraphicsView::centerOn(15000, 15000);
    sceneObj->mouseGrabberItem();

    penSelectedKnot.setColor(Qt::green);
    penSelectedKnot.setWidth(3);

    drawing();

    timer = new QTimer();
    timer->setSingleShot(true);
    timer->start(50);

    timerMouseEvent = new QTimer();
    connect(timerMouseEvent, SIGNAL(timeout()), this, SLOT(slotTimer()));
    timerMouseEvent->start(50);
}



void GrphicScene::drawing(){
    this->deleteItemGroup();

    QPen pen(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(2);

    QPen penText(Qt::black);
    penText.setWidth(1);

    QBrush brushText(Qt::black);

    if(knotCount == 0){
        storageObj.knotChange(knotCount, 15000, 15000, 100, 50, -1, 0);

        QPoint point;
        point.setX(15000 + 5);
        point.setY(15000 + 25);

        QFont font;
        font.setPixelSize(14);

        pathText.push_back(QPainterPath());
        pathText.back().addText(point, font, storageObj.getText(knotCount));

        storageObj.addKnot(0);
        ++knotCount;
    }

    for(int i = 0; i < knotCount; ++i){
        int x = storageObj.knotStartPosition_X(i);
        int y = storageObj.knotStartPosition_Y(i);

        int w = storageObj.knotWidth(i);
        int h = storageObj.knotHeight(i);

        if(i == indexSelectedKnot){
            group->addToGroup(sceneObj->addEllipse(x, y, w, h, penSelectedKnot));
        }
        else{
            group->addToGroup(sceneObj->addEllipse(x, y, w, h, pen));
        }

        group->addToGroup(sceneObj->addPath(pathText[i], penText, brushText));
    }

    for(int i = 0; i < path.size(); ++i){
        group->addToGroup(sceneObj->addPath(path[i], pen));
    }
}



void GrphicScene::drawingOutOfOut(){
    choiceObj.calculation(indexSelectedKnot);

    int startPosition_X = choiceObj.getStartPosition_X();
    int startPosition_Y = choiceObj.getStartPosition_Y();
    int endPosition_X = choiceObj.getEndPosition_X();
    int endPosition_Y = choiceObj.getEndPosition_Y();

    int cornerEarth = choiceObj.getCornerEarth();

    int c1_X = choiceObj.getC1_X();
    int c1_Y = choiceObj.getC1_Y();
    int c2_X = choiceObj.getC2_X();
    int c2_Y = choiceObj.getC2_Y();

    int width = 100;
    int height = 50;


    drawingBezier(startPosition_X, startPosition_Y, c1_X, c1_Y, c2_X, c2_Y, endPosition_X, endPosition_Y, cornerEarth, width, height);

    drawingKnot(endPosition_X, endPosition_Y, width, height, cornerEarth);

    storageObj.knotChangeIndexChildKnot(indexSelectedKnot, storageObj.knotCountChildKnot(indexSelectedKnot), knotCount - 1);

    choiceObj.calculationNewPosition(0);
    updateCurveBezier();
    updateText();

    drawing();
}



void GrphicScene::drawingBezier(int startPos_X, int startPos_Y, int c1_X, int c1_Y, int c2_X, int c2_Y, int endPos_X, int endPos_Y, int cornerEarth, int width, int height){
    storageObj.curveChange(curveCount, indexSelectedKnot, startPos_X, startPos_Y, endPos_X, endPos_Y, c1_X, c1_Y, c2_X, c2_Y);

    if(cornerEarth == 1){
        if(endPos_X <= startPos_X){
            c1_X -= (width - width % 2) / 2;

            c2_X -= (width - width % 2) / 2;
            c2_Y += (height - height % 2) / 2;
        }
        else{
            c1_X += (width - width % 2) / 2;

            c2_X += (width - width % 2) / 2;
            c2_Y += (height - height % 2) / 2;
        }

        endPos_X += (width - width % 2) / 2;
        endPos_Y += height;

    }
    else if(cornerEarth == 2){
        if(endPos_Y <= startPos_Y){
            c1_Y -= (height - height % 2) / 2;

            c2_X -= (width - width % 2) / 2;
            c2_Y -= (height - height % 2) / 2;
        }
        else{
            c1_Y += (height - height % 2) / 2;

            c2_X -= (width - width % 2) / 2;
            c2_Y += (height - height % 2) / 2;
        }

        endPos_Y += (height - height % 2) / 2;
    }
    else if(cornerEarth == 3){
        if(endPos_X >= startPos_X){
            c1_X += (width - width % 2) / 2;

            c2_X += (width - width % 2) / 2;
            c2_Y -= (height - height % 2) / 2;
        }
        else{
            c1_X -= (width - width % 2) / 2;

            c2_X -= (width - width % 2) / 2;
            c2_Y -= (height - height % 2) / 2;
        }

        endPos_X += (width - width % 2) / 2;
    }
    else{
        if(endPos_Y >= startPos_Y){
            c1_Y += (height - height % 2) / 2;

            c2_X += (width - width % 2) / 2;
            c2_Y += (height - height % 2) / 2;
        }
        else{
            c1_Y -= (height - height % 2) / 2;

            c2_X += (width - width % 2) / 2;
            c2_Y -= (height - height % 2) / 2;
        }

        endPos_X += width;
        endPos_Y += (height - height % 2) / 2;
    }

    QPointF c1;
    c1.setX(c1_X);
    c1.setY(c1_Y);

    QPointF c2;
    c2.setX(c2_X);
    c2.setY(c2_Y);

    QPointF endPosition;
    endPosition.setX(endPos_X);
    endPosition.setY(endPos_Y);

    QPointF startPosition;
    startPosition.setX(startPos_X);
    startPosition.setY(startPos_Y);

    path.push_back(QPainterPath(startPosition));
    path.back().cubicTo(c1,c2,endPosition);

    ++curveCount;
}



void GrphicScene::drawingKnot(int startPos_X, int startPos_Y, int width, int height, int cornerEarth){
    storageObj.knotChange(knotCount, startPos_X, startPos_Y, width, height, indexSelectedKnot, cornerEarth);

    QPoint point;
    point.setX(startPos_X + 5);
    point.setY(startPos_Y + ((height - height % 2) / 2));

    QFont font;
    font.setPixelSize(14);

    pathText.push_back(QPainterPath());
    pathText.back().addText(point, font, storageObj.getText(knotCount));

    storageObj.addKnot(curveCount);
    storageObj.knotChangeIndexCurve(knotCount, curveCount - 1);
    ++knotCount;
}



void GrphicScene::resizeEvent(QResizeEvent *event){
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}



void GrphicScene::deleteItemGroup(){
    foreach(QGraphicsItem *item, sceneObj->items(group->boundingRect())){
        if(item->group() == group){
            delete item;
        }
    }
}



void GrphicScene::updateCurveBezier(){
    QPointF c1;
    QPointF c2;
    QPointF endPosition;
    QPointF startPosition;

    int c1_X;
    int c1_Y;
    int c2_X;
    int c2_Y;

    int count = path.size();

    choiceObj.calculationNewPosition(0);

    for(int i = 0; i < count; ++i){
        path.pop_back();
    }

    for(int i = 0; i < count; ++i){
        c1_X = storageObj.curveStartPosition_X(i);
        c1_Y = storageObj.curveStartPosition_Y(i);

        c2_X = storageObj.curveEndPosition_X(i);
        c2_Y = storageObj.curveEndPosition_Y(i);

        int endPos_X = storageObj.curveEndPosition_X(i);
        int endPos_Y = storageObj.curveEndPosition_Y(i);

        int width = storageObj.knotWidth(i + 1);
        int height = storageObj.knotHeight(i + 1);

        int cornerEarth = storageObj.knotCornerEarth(i + 1);

        if(cornerEarth == 1){
            if(endPos_X <= storageObj.curveStartPosition_X(i)){
                c1_X -= (width - width % 2) / 2;

                c2_X -= (width - width % 2) / 2;
                c2_Y += (height - height % 2) / 2;
            }
            else{
                c1_X += (width - width % 2) / 2;

                c2_X += (width - width % 2) / 2;
                c2_Y += (height - height % 2) / 2;
            }

            endPos_X += (width - width % 2) / 2;
            endPos_Y += height;

        }
        else if(cornerEarth == 2){
            if(endPos_Y <= storageObj.curveStartPosition_Y(i)){
                c1_Y -= (height - height % 2) / 2;

                c2_X -= (width - width % 2) / 2;
                c2_Y -= (height - height % 2) / 2;
            }
            else{
                c1_Y += (height - height % 2) / 2;

                c2_X -= (width - width % 2) / 2;
                c2_Y += (height - height % 2) / 2;
            }

            endPos_Y += (height - height % 2) / 2;
        }
        else if(cornerEarth == 3){
            if(endPos_X >= storageObj.curveStartPosition_X(i)){
                c1_X += (width - width % 2) / 2;

                c2_X += (width - width % 2) / 2;
                c2_Y -= (height - height % 2) / 2;
            }
            else{
                c1_X -= (width - width % 2) / 2;

                c2_X -= (width - width % 2) / 2;
                c2_Y -= (height - height % 2) / 2;
            }

            endPos_X += (width - width % 2) / 2;
        }
        else{
            if(endPos_Y >= storageObj.curveStartPosition_Y(i)){
                c1_Y += (height - height % 2) / 2;

                c2_X += (width - width % 2) / 2;
                c2_Y += (height - height % 2) / 2;
            }
            else{
                c1_Y -= (height - height % 2) / 2;

                c2_X += (width - width % 2) / 2;
                c2_Y -= (height - height % 2) / 2;
            }

            endPos_X += width;
            endPos_Y += (height - height % 2) / 2;
        }

        c1.setX(c1_X);
        c1.setY(c1_Y);

        c2.setX(c2_X);
        c2.setY(c2_Y);

        startPosition.setX(storageObj.curveStartPosition_X(i));
        startPosition.setY(storageObj.curveStartPosition_Y(i));

        endPosition.setX(endPos_X);
        endPosition.setY(endPos_Y);

        path.push_back(QPainterPath(startPosition));
        path.back().cubicTo(c1,c2,endPosition);
    }
}



void GrphicScene::updateChildCurve(){
    int index;
    int startPosX = storageObj.knotStartPosition_X(indexSelectedKnot);
    int startPosY = storageObj.knotStartPosition_Y(indexSelectedKnot);

    for(int i = 0; i < storageObj.knotCountChildKnot(indexSelectedKnot); ++i){
        index = storageObj.knotIndexChildKnot(indexSelectedKnot, i);

        if(storageObj.knotCornerEarth(index) == 1){
            startPosX -= (storageObj.knotWidth(indexSelectedKnot) - storageObj.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY -= (storageObj.knotHeight(indexSelectedKnot) - storageObj.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else if(storageObj.knotCornerEarth(index) == 2){
            startPosX += storageObj.knotWidth(indexSelectedKnot);
            startPosY += (storageObj.knotHeight(indexSelectedKnot) - storageObj.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else if(storageObj.knotCornerEarth(index) == 3){
            startPosX += (storageObj.knotWidth(indexSelectedKnot) - storageObj.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY += (storageObj.knotHeight(indexSelectedKnot) - storageObj.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else{
            startPosX -= (storageObj.knotWidth(indexSelectedKnot) - storageObj.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY += (storageObj.knotHeight(indexSelectedKnot) - storageObj.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        storageObj.curveChangeStartPosition(storageObj.knotIndexCurve(index), startPosX, startPosY);
    }
}



void GrphicScene::updateText(){
    for(int i = 0; i < knotCount; ++i){
        pathText.pop_back();
    }

    QPoint point;

    QFont font;
    font.setPixelSize(14);

    for(int i = 0; i < knotCount; ++i){
        point.setX(storageObj.knotStartPosition_X(i) + 5);
        point.setY(storageObj.knotStartPosition_Y(i) + (storageObj.knotHeight(i) - storageObj.knotHeight(i) % 2) / 2);

        pathText.push_back(QPainterPath());

        if(i == indexSelectedKnot){
            pathText.back().addText(point, font, storageObj.getAllText(i));
        }
        else{
            pathText.back().addText(point, font, storageObj.getText(i));
        }
    }
}



void GrphicScene::slotTimer(){
    if(sceneObj->getSelectedStatusFlag()){
        indexSelectedKnot = sceneObj->getSelectedKnot();

        updateText();
        drawing();
    }

    if(sceneObj->getMoveStatusFlag()){
        if(storageObj.knotCountChildKnot(indexSelectedKnot) > 0){
            updateChildCurve();
        }

        updateCurveBezier();

        updateText();
        drawing();

        sceneObj->setMoveStatusFlag(false);
    }

    if(sceneObj->getTextFlag()){
        storageObj.setText(indexSelectedKnot, sceneObj->getText());
        sceneObj->clearText();

        updateText();
        drawing();
    }

    if(sceneObj->getTextBackFlag()){
        sceneObj->setTextBackFlag();

        updateText();
        drawing();
    }
}
