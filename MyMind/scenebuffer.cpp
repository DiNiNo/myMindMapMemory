#include "scenebuffer.h"

SceneBuffer::SceneBuffer(){}



void SceneBuffer::setSelectedKnot(int value){
    selectedKnot = value;
    statusFlag = true;
}


void SceneBuffer::setMoveStatusFlag(bool value){
    moveStatusFlag = value;
}




int SceneBuffer::getSelectedKnot(){
    if(statusFlag){
        statusFlag = false;
        return selectedKnot;
    }
    else{
        return 0;
    }
}



bool SceneBuffer::getStatusFlag(){
    return statusFlag;
}



bool SceneBuffer::getMoveStatusFlag(){
    return moveStatusFlag;
}



int SceneBuffer::selectedKnot = 0;

bool SceneBuffer::statusFlag = false;
bool SceneBuffer::moveStatusFlag = false;
