#include "graphicsceneevent.h"

GraphicSceneEvent::GraphicSceneEvent(QObject *parent) : QGraphicsScene (parent){}



void GraphicSceneEvent::setMoveStatusFlag(bool value){
    moveStatusFlag = value;
}



int GraphicSceneEvent::getSelectedKnot(){
    if(selectedStatusFlag){
        selectedStatusFlag = false;
        return indexSelectedKnot;
    }
    else{
        return 0;
    }
}



bool GraphicSceneEvent::getSelectedStatusFlag(){
    return selectedStatusFlag;
}



bool GraphicSceneEvent::getMoveStatusFlag(){
    return moveStatusFlag;
}



void GraphicSceneEvent::clearText(){
    text = "";
}



void GraphicSceneEvent::setTextBackFlag(){
    textBackFlag = false;
}



QString GraphicSceneEvent::getText(){
    if(textFlag){
        textFlag = false;
        return text;
    }
    else{
        return "";
    }
}



bool GraphicSceneEvent::getTextFlag(){
    return textFlag;
}



bool GraphicSceneEvent::getTextBackFlag(){
    return textBackFlag;
}



void GraphicSceneEvent::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    text = "";

    selectedKnot(x, y);
}



void GraphicSceneEvent::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        int x = event->scenePos().x();
        int y = event->scenePos().y();

        if(indexSelectedKnot > 0){
            storagePoints.curveChangeEndPosition(indexSelectedKnot - 1, x, y);
        }

        storagePoints.knotChange(indexSelectedKnot, x, y);

        moveStatusFlag = true;
    }
}



void GraphicSceneEvent::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Backspace){
        storagePoints.popBackText(indexSelectedKnot);
        textBackFlag = true;
    }
    else if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        text = "";
    }
    else {
        text += event->text();
        textFlag = true;
    }
}



void GraphicSceneEvent::selectedKnot(int x, int y){
    int posX, posY;
    bool flag = false;

    for(int i = 0; i < 200; ++i){
        posX = storagePoints.knotStartPosition_X(i);
        posY = storagePoints.knotStartPosition_Y(i);

        if(posX < x && (posX + storagePoints.knotWidth(i)) > x && posY < y && (posY + storagePoints.knotHeight(i)) > y){
            flag = true;

            indexSelectedKnot = i;
            selectedStatusFlag = true;
        }
    }

    if(!flag){
        indexSelectedKnot = -1;
        selectedStatusFlag = false;
    }
}
