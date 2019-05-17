#include "storagepoints.h"

StoragePoints::StoragePoints(){
}



//set knot
void StoragePoints::knotChange(int index, int startPosition_X, int startPosition_Y, int width, int height, int indexParentKnot, int cornerEarth){
    knotStorage[index].startPosition_X = startPosition_X;
    knotStorage[index].startPosition_Y = startPosition_Y;
    knotStorage[index].width = width;
    knotStorage[index].height = height;
    knotStorage[index].indexParentKnot = indexParentKnot;
    knotStorage[index].cornerEarth = cornerEarth;
}



void StoragePoints::knotChange(int index, int startPosition_X, int startPosition_Y){
    knotStorage[index].startPosition_X = startPosition_X;
    knotStorage[index].startPosition_Y = startPosition_Y;
}



void StoragePoints::knotChange(int index, int indexParentKnot){
    knotStorage[index].indexParentKnot = indexParentKnot;
}



void StoragePoints::knotChangeSize(int index, int width, int height){
    knotStorage[index].width = width;
    knotStorage[index].height = height;
}



void StoragePoints::knotChangeWidth(int index, int width){
    knotStorage[index].width = width;
}



void StoragePoints::knotChangeHeight(int index, int height){
    knotStorage[index].height = height;
}



void StoragePoints::knotChangeIndexChildKnot(int index, int indexChildKnotSelected, int indexChildKnotValue){
    knotStorage[index].indexChildKnot[indexChildKnotSelected] = indexChildKnotValue;
    ++knotStorage[index].countChildKnot;
}



void StoragePoints::knotChangeCornerEarth(int index, int cornerEarth){
    knotStorage[index].cornerEarth = cornerEarth;
}



void StoragePoints::knotChangeStartPosition_X(int index, int startPosition_X){
    knotStorage[index].startPosition_X = startPosition_X;
}



void StoragePoints::knotChangeStartPosition_Y(int index, int startPosition_Y){
    knotStorage[index].startPosition_Y = startPosition_Y;
}



void StoragePoints::knotChangeIndexCurve(int index, int value){
    knotStorage[index].indexCurve = value;
}



//get knot
int StoragePoints::knotStartPosition_X(int index){
    return knotStorage[index].startPosition_X;
}



int StoragePoints::knotStartPosition_Y(int index){
    return knotStorage[index].startPosition_Y;
}



int StoragePoints::knotWidth(int index){
    return knotStorage[index].width;
}



int StoragePoints::knotHeight(int index){
    return knotStorage[index].height;
}



int StoragePoints::knotIndexParentKnot(int index){
    return knotStorage[index].indexParentKnot;
}



int StoragePoints::knotIndexChildKnot(int index, int indexChildKnotSelected){
    return knotStorage[index].indexChildKnot[indexChildKnotSelected];
}



int StoragePoints::knotCountChildKnot(int index){
    return knotStorage[index].countChildKnot;
}



int StoragePoints::knotCornerEarth(int index){
    return knotStorage[index].cornerEarth;
}



int StoragePoints::knotIndexCurve(int index){
    return knotStorage[index].indexCurve;
}



//set curve
void StoragePoints::curveChange(int index, int indexParentKnot, int startPosition_X, int startPosition_Y, int endPosition_X, int endPosition_Y, int c1_X, int c1_Y, int c2_X, int c2_Y){
    curveStorage[index].indexParentKnot = indexParentKnot;
    curveStorage[index].startPosition_X = startPosition_X;
    curveStorage[index].startPosition_Y = startPosition_Y;
    curveStorage[index].endPosition_X = endPosition_X;
    curveStorage[index].endPosition_Y = endPosition_Y;
    curveStorage[index].c1_X = c1_X;
    curveStorage[index].c1_Y = c1_Y;
    curveStorage[index].c2_X = c2_X;
    curveStorage[index].c2_Y = c2_Y;
}



void StoragePoints::curveChange(int index, int indexParentKnot){
    curveStorage[index].indexParentKnot = indexParentKnot;
}



void StoragePoints::curveChangeStartPosition(int index, int startPosition_X, int startPosition_Y){
    curveStorage[index].startPosition_X = startPosition_X;
    curveStorage[index].startPosition_Y = startPosition_Y;
}



void StoragePoints::curveChangeEndPosition(int index, int endPosition_X, int endPosition_Y){
    curveStorage[index].endPosition_X = endPosition_X;
    curveStorage[index].endPosition_Y = endPosition_Y;
}



void StoragePoints::curveChangeEndPosition_X(int index, int endPosition_X){
    curveStorage[index].endPosition_X = endPosition_X;
}



void StoragePoints::curveChangeEndPosition_Y(int index, int endPosition_Y){
    curveStorage[index].endPosition_Y = endPosition_Y;
}



void StoragePoints::curveChangeC1(int index, int c1_X, int c1_Y){
    curveStorage[index].c1_X = c1_X;
    curveStorage[index].c1_Y = c1_Y;
}



void StoragePoints::curveChangeC2(int index, int c2_X, int c2_Y){
    curveStorage[index].c2_X = c2_X;
    curveStorage[index].c2_Y = c2_Y;
}



//get curve
int StoragePoints::curveIndexParentKnot(int index){
    return curveStorage[index].indexParentKnot;
}



int StoragePoints::curveStartPosition_X(int index){
    return curveStorage[index].startPosition_X;
}



int StoragePoints::curveStartPosition_Y(int index){
    return curveStorage[index].startPosition_Y;
}



int StoragePoints::curveEndPosition_X(int index){
    return curveStorage[index].endPosition_X;
}



int StoragePoints::curveEndPosition_Y(int index){
    return curveStorage[index].endPosition_Y;
}



int StoragePoints::curveC1_X(int index){
    return curveStorage[index].c1_X;
}



int StoragePoints::curveC1_Y(int index){
    return curveStorage[index].c1_Y;
}



int StoragePoints::curveC2_X(int index){
    return curveStorage[index].c2_X;
}



int StoragePoints::curveC2_Y(int index){
    return curveStorage[index].c2_Y;
}



//set indexKnotNCurve
void StoragePoints::addKnot(int indexCurve){
    indexKnotNCurve.push_back(indexCurve);
}



void StoragePoints::changeKnot(int indexKnot, int indexCurve){
    indexKnotNCurve[indexKnot] = indexCurve;
}



//get indexKnotNCurve
int StoragePoints::getCurveIndex(int indexKnot){
    return indexKnotNCurve[indexKnot];
}



//set text
void StoragePoints::setText(int indexKnot, QString value){
    if(knotStorage[indexKnot].text.size() < 10){
        knotStorage[indexKnot].text += value;
    }
    knotStorage[indexKnot].allText += value;
}



void StoragePoints::popBackText(int indexKnot){
    int size = knotStorage[indexKnot].allText.size();

    if(size == 10){
        knotStorage[indexKnot].text.chop(1);
        }

    knotStorage[indexKnot].allText.chop(1);
}



//get text
QString StoragePoints::getText(int indexKnot){
    return knotStorage[indexKnot].text;
}



QString StoragePoints::getAllText(int indexKnot){
    return knotStorage[indexKnot].allText;
}



StoragePoints::knotStruct* StoragePoints::knotStorage = new StoragePoints::knotStruct [200];
StoragePoints::curveBezierStruct* StoragePoints::curveStorage = new StoragePoints::curveBezierStruct[200];
QVector<int> StoragePoints::indexKnotNCurve;
