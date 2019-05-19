#include "graphicscene.h"

GraphicScene::GraphicScene(QWidget *parent) : QGraphicsView (parent){
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



void GraphicScene::drawing(){
    this->deleteItemGroup();

    QPen pen(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(2);

    QPen penText(Qt::black);
    penText.setWidth(1);

    QBrush brushText(Qt::black);

    if(knotCount == 0){
        storagePoints.knotChange(knotCount, 15000, 15000, 100, 50, -1, 0);

        QPoint point;
        point.setX(15000 + 5);
        point.setY(15000 + 25);

        QFont font;
        font.setPixelSize(14);

        pathText.push_back(QPainterPath());
        pathText.back().addText(point, font, storagePoints.getText(knotCount));

        storagePoints.addKnot(0);
        ++knotCount;
    }

    for(int i = 0; i < knotCount; ++i){
        int x = storagePoints.knotStartPosition_X(i);
        int y = storagePoints.knotStartPosition_Y(i);

        int w = storagePoints.knotWidth(i);
        int h = storagePoints.knotHeight(i);

        if(i == indexSelectedKnot){
            group->addToGroup(sceneObj->addEllipse(x, y, w, h, penSelectedKnot));
        }
        else{
            group->addToGroup(sceneObj->addEllipse(x, y, w, h, pen));
        }

        group->addToGroup(sceneObj->addPath(pathText[i], penText, brushText));
    }

    for(int i = 0; i < pathCurve.size(); ++i){
        group->addToGroup(sceneObj->addPath(pathCurve[i], pen));
    }
}



void GraphicScene::drawingOutOfOut(){
    choiceBuild.calculation(indexSelectedKnot);

    int startPosition_X = choiceBuild.getStartPosition_X();
    int startPosition_Y = choiceBuild.getStartPosition_Y();
    int endPosition_X = choiceBuild.getEndPosition_X();
    int endPosition_Y = choiceBuild.getEndPosition_Y();

    int cornerEarth = choiceBuild.getCornerEarth();

    int width = 100;
    int height = 50;


    drawingBezier(startPosition_X, startPosition_Y, endPosition_X, endPosition_Y, cornerEarth, width, height);

    drawingKnot(endPosition_X, endPosition_Y, width, height, cornerEarth);

    storagePoints.knotChangeIndexChildKnot(indexSelectedKnot, storagePoints.knotCountChildKnot(indexSelectedKnot), knotCount - 1);

    choiceBuild.calculationNewPosition(0);
    updateCurveBezier();
    updateText();

    drawing();
}



void GraphicScene::drawingBezier(int startPos_X, int startPos_Y, int endPos_X, int endPos_Y, int cornerEarth, int width, int height){
    storagePoints.curveChange(curveCount, indexSelectedKnot, startPos_X, startPos_Y, endPos_X, endPos_Y);

    if(cornerEarth == 1){
        endPos_X += (width - width % 2) / 2;
        endPos_Y += height;
    }
    else if(cornerEarth == 2){
        endPos_Y += (height - height % 2) / 2;
    }
    else if(cornerEarth == 3){
        endPos_X += (width - width % 2) / 2;
    }
    else{
        endPos_X += width;
        endPos_Y += (height - height % 2) / 2;
    }

    QVector<int> CPoints = calculationCPoints(startPos_X, startPos_Y, endPos_X, endPos_Y, width, height, cornerEarth);

    int c1_X = CPoints[0];
    int c1_Y = CPoints[1];

    int c2_X = CPoints[2];
    int c2_Y = CPoints[3];

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

    pathCurve.push_back(QPainterPath(startPosition));
    pathCurve.back().cubicTo(c1,c2,endPosition);

    ++curveCount;
}



void GraphicScene::drawingKnot(int startPos_X, int startPos_Y, int width, int height, int cornerEarth){
    storagePoints.knotChange(knotCount, startPos_X, startPos_Y, width, height, indexSelectedKnot, cornerEarth);

    QPoint point;
    point.setX(startPos_X + 5);
    point.setY(startPos_Y + ((height - height % 2) / 2));

    QFont font;
    font.setPixelSize(14);

    pathText.push_back(QPainterPath());
    pathText.back().addText(point, font, storagePoints.getText(knotCount));

    storagePoints.addKnot(curveCount);
    storagePoints.knotChangeIndexCurve(knotCount, curveCount - 1);
    ++knotCount;
}



void GraphicScene::resizeEvent(QResizeEvent *event){
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}



void GraphicScene::deleteItemGroup(){
    foreach(QGraphicsItem *item, sceneObj->items(group->boundingRect())){
        if(item->group() == group){
            delete item;
        }
    }
}



void GraphicScene::updateCurveBezier(){
    QPointF c1;
    QPointF c2;
    QPointF endPosition;
    QPointF startPosition;

    QVector<int> CPoints;

    int c1_X;
    int c1_Y;
    int c2_X;
    int c2_Y;

    int count = pathCurve.size();

    choiceBuild.calculationNewPosition(0);

    for(int i = 0; i < count; ++i){
        pathCurve.pop_back();
    }

    for(int i = 0; i < count; ++i){
        int endPos_X = storagePoints.curveEndPosition_X(i);
        int endPos_Y = storagePoints.curveEndPosition_Y(i);

        int width = storagePoints.knotWidth(i + 1);
        int height = storagePoints.knotHeight(i + 1);

        int cornerEarth = storagePoints.knotCornerEarth(i + 1);

        if(cornerEarth == 1){
            endPos_X += (width - width % 2) / 2;
            endPos_Y += height;

        }
        else if(cornerEarth == 2){
            endPos_Y += (height - height % 2) / 2;
        }
        else if(cornerEarth == 3){
            endPos_X += (width - width % 2) / 2;
        }
        else{
            endPos_X += width;
            endPos_Y += (height - height % 2) / 2;
        }

        CPoints = calculationCPoints(storagePoints.curveStartPosition_X(i), storagePoints.curveStartPosition_Y(i), endPos_X, endPos_Y, width, height, cornerEarth);

        c1_X = CPoints[0];
        c1_Y = CPoints[1];

        c2_X = CPoints[2];
        c2_Y = CPoints[3];

        c1.setX(c1_X);
        c1.setY(c1_Y);

        c2.setX(c2_X);
        c2.setY(c2_Y);

        startPosition.setX(storagePoints.curveStartPosition_X(i));
        startPosition.setY(storagePoints.curveStartPosition_Y(i));

        endPosition.setX(endPos_X);
        endPosition.setY(endPos_Y);

        pathCurve.push_back(QPainterPath(startPosition));
        pathCurve.back().cubicTo(c1,c2,endPosition);
    }
}



void GraphicScene::updateChildCurve(){
    int index;
    int startPosX = storagePoints.knotStartPosition_X(indexSelectedKnot);
    int startPosY = storagePoints.knotStartPosition_Y(indexSelectedKnot);

    for(int i = 0; i < storagePoints.knotCountChildKnot(indexSelectedKnot); ++i){
        index = storagePoints.knotIndexChildKnot(indexSelectedKnot, i);

        if(storagePoints.knotCornerEarth(index) == 1){
            startPosX -= (storagePoints.knotWidth(indexSelectedKnot) - storagePoints.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY -= (storagePoints.knotHeight(indexSelectedKnot) - storagePoints.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else if(storagePoints.knotCornerEarth(index) == 2){
            startPosX += storagePoints.knotWidth(indexSelectedKnot);
            startPosY += (storagePoints.knotHeight(indexSelectedKnot) - storagePoints.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else if(storagePoints.knotCornerEarth(index) == 3){
            startPosX += (storagePoints.knotWidth(indexSelectedKnot) - storagePoints.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY += (storagePoints.knotHeight(indexSelectedKnot) - storagePoints.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        else{
            startPosX -= (storagePoints.knotWidth(indexSelectedKnot) - storagePoints.knotWidth(indexSelectedKnot) % 2) / 2;
            startPosY += (storagePoints.knotHeight(indexSelectedKnot) - storagePoints.knotHeight(indexSelectedKnot) % 2) / 2;
        }
        storagePoints.curveChangeStartPosition(storagePoints.knotIndexCurve(index), startPosX, startPosY);
    }
}



void GraphicScene::updateText(){
    for(int i = 0; i < knotCount; ++i){
        pathText.pop_back();
    }

    QPoint point;

    QFont font;
    font.setPixelSize(14);

    for(int i = 0; i < knotCount; ++i){
        point.setX(storagePoints.knotStartPosition_X(i) + 5);
        point.setY(storagePoints.knotStartPosition_Y(i) + (storagePoints.knotHeight(i) - storagePoints.knotHeight(i) % 2) / 2);

        pathText.push_back(QPainterPath());

        if(i == indexSelectedKnot){
            pathText.back().addText(point, font, storagePoints.getAllText(i));
        }
        else{
            pathText.back().addText(point, font, storagePoints.getText(i));
        }
    }
}



void GraphicScene::slotTimer(){
    if(sceneObj->getSelectedStatusFlag()){
        indexSelectedKnot = sceneObj->getSelectedKnot();

        updateText();
        drawing();
    }

    if(sceneObj->getMoveStatusFlag()){
        if(storagePoints.knotCountChildKnot(indexSelectedKnot) > 0){
            updateChildCurve();
        }

        updateCurveBezier();

        updateText();
        drawing();

        sceneObj->setMoveStatusFlag(false);
    }

    if(sceneObj->getTextFlag()){
        storagePoints.setText(indexSelectedKnot, sceneObj->getText());
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




QVector<int> GraphicScene::calculationCPoints(int c1X, int c1Y, int c2X, int c2Y, int width, int height, int cornerEarth){
    if(cornerEarth == 1){
        if(c2X <= c1X){
            c1X -= (width - width % 2) / 2;

            c2X -= (width - width % 2) / 2;
            c2Y += (height - height % 2) / 2;
        }
        else{
            c1X += (width - width % 2) / 2;

            c2X += (width - width % 2) / 2;
            c2Y += (height - height % 2) / 2;
        }
    }
    else if(cornerEarth == 2){
        if(c2Y <= c1Y){
            c1Y -= (height - height % 2) / 2;

            c2X -= (width - width % 2) / 2;
            c2Y -= (height - height % 2) / 2;
        }
        else{
            c1Y += (height - height % 2) / 2;

            c2X -= (width - width % 2) / 2;
            c2Y += (height - height % 2) / 2;
        }
    }
    else if(cornerEarth == 3){
        if(c2X >= c1X){
            c1X += (width - width % 2) / 2;

            c2X += (width - width % 2) / 2;
            c2Y -= (height - height % 2) / 2;
        }
        else{
            c1X -= (width - width % 2) / 2;

            c2X -= (width - width % 2) / 2;
            c2Y -= (height - height % 2) / 2;
        }
    }
    else{
        if(c2Y >= c1Y){
            c1Y += (height - height % 2) / 2;

            c2X += (width - width % 2) / 2;
            c2Y += (height - height % 2) / 2;
        }
        else{
            c1Y -= (height - height % 2) / 2;

            c2X += (width - width % 2) / 2;
            c2Y -= (height - height % 2) / 2;
        }
    }

    QVector<int> value;

    value.push_back(c1X);
    value.push_back(c1Y);

    value.push_back(c2X);
    value.push_back(c2Y);

    return value;
}
