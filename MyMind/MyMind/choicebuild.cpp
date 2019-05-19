#include "choicebuild.h"

ChoiceBuild::ChoiceBuild(){
}



void ChoiceBuild::calculation(int indexParentKnot){
    storageCoord.cornerEarth = calculationCornerEarth(indexParentKnot);
    calculationStartPosition(indexParentKnot);
    calculationEndPosition(indexParentKnot);
    //calculationNewPosition();
}



int ChoiceBuild::getStartPosition_X(){
    return storageCoord.startPosition_X;
}



int ChoiceBuild::getStartPosition_Y(){
    return storageCoord.startPosition_Y;
}



int ChoiceBuild::getEndPosition_X(){
    return storageCoord.endPosition_X;
}



int ChoiceBuild::getEndPosition_Y(){
    return storageCoord.endPosition_Y;
}



int ChoiceBuild::getCornerEarth(){
    return storageCoord.cornerEarth;
}



int ChoiceBuild::calculationCornerEarth(int index){
    int cornerEarthNorth = 0;
    int cornerEarthEastern = 0;
    int cornerEarthSouth = 0;
    int cornerEarthWest = 0;
    int cornerEarth = 0;

    for(int i = 0; i < storagePoints.knotCountChildKnot(index); ++i){
        cornerEarth = storagePoints.knotCornerEarth(storagePoints.knotIndexChildKnot(index, i));

        if(cornerEarth == 1){
            ++cornerEarthNorth;
        }
        else if(cornerEarth == 2){
            ++cornerEarthEastern;
        }
        else if(cornerEarth == 3){
            ++cornerEarthSouth;
        }
        else if(cornerEarth == 4){
            ++cornerEarthWest;
        }
    }

    cornerEarth = storagePoints.knotCornerEarth(index);

    if(cornerEarthNorth == cornerEarthEastern && cornerEarthNorth == cornerEarthSouth && cornerEarthSouth == cornerEarthWest){
        if(cornerEarth == 2){
            return 4;
        }
        else{
            return 2;
        }
    }
    else if(cornerEarth != 1 && cornerEarthNorth < cornerEarthEastern){
        return 1;
    }
    else if(cornerEarth != 2 && cornerEarthEastern < cornerEarthSouth){
        return 2;
    }
    else if(cornerEarth != 3 && cornerEarthSouth < cornerEarthWest){
        return 3;
    }
    else {
        return 4;
    }
}



void ChoiceBuild::calculationStartPosition(int index){
    int step;

    if(storageCoord.cornerEarth == 1 || storageCoord.cornerEarth == 3){
        if(storageCoord.cornerEarth == 1){
            storageCoord.startPosition_Y = storagePoints.knotStartPosition_Y(index);
        }
        else{
            step = storagePoints.knotHeight(index);
            storageCoord.startPosition_Y = storagePoints.knotStartPosition_Y(index) + step;
        }

        step = storagePoints.knotWidth(index);
        storageCoord.startPosition_X = storagePoints.knotStartPosition_X(index) + (step - step%2)/2;
    }
    else{
        if(storageCoord.cornerEarth == 4){
            storageCoord.startPosition_X = storagePoints.knotStartPosition_X(index);
        }
        else{
            step = storagePoints.knotWidth(index);
            storageCoord.startPosition_X = storagePoints.knotStartPosition_X(index) + step;
        }

        step = storagePoints.knotHeight(index);
        storageCoord.startPosition_Y = storagePoints.knotStartPosition_Y(index) + (step - step%2)/2;
    }
}



void ChoiceBuild::calculationEndPosition(int index){

    int* indexChildKnot = new int[storagePoints.knotCountChildKnot(index)];

    int j = 0;

    for(int i = 0; i < storagePoints.knotCountChildKnot(index); ++i){
        if(storageCoord.cornerEarth == storagePoints.knotCornerEarth(storagePoints.knotIndexChildKnot(index, i))){
            indexChildKnot[j] = storagePoints.knotIndexChildKnot(index, i);
            ++j;
        }
    }

    int max = 0, min = 300000;
    int endPos;

    if(storageCoord.cornerEarth == 1 || storageCoord.cornerEarth == 3){
        for(int i = 0; i < j; ++i){
            if(storageCoord.cornerEarth == 1){
                endPos = storagePoints.knotStartPosition_X(indexChildKnot[i]) + ((storagePoints.knotWidth(indexChildKnot[i]) - storagePoints.knotWidth(indexChildKnot[i]) % 2) / 2);
            }
            else{
                endPos = storagePoints.knotStartPosition_X(indexChildKnot[i]) - ((storagePoints.knotWidth(indexChildKnot[i]) - storagePoints.knotWidth(indexChildKnot[i]) % 2) / 2);
            }

            if(endPos > max){
                max = endPos;
            }
            if(endPos < min){
                min = endPos;
            }
        }

        int step = max - min;
        step = (step - step % 2) / 2;

        if(j == 0){
            storageCoord.endPosition_X = storagePoints.knotStartPosition_X(index) + ((storagePoints.knotWidth(index) - storagePoints.knotWidth(index) % 2) / 2);
        }
        else{
            if(storageCoord.startPosition_X - step < min){
                storageCoord.endPosition_X = min - 75;
            }
            else{
                storageCoord.endPosition_X = max + 75;
            }
        }


        if(storageCoord.cornerEarth == 1){
            storageCoord.endPosition_Y = storageCoord.startPosition_Y - 150;
        }
        else{
            storageCoord.endPosition_Y = storageCoord.startPosition_Y + 150;
        }
    }
    else{
        for(int i = 0; i < j; ++i) {
            if(storageCoord.cornerEarth == 2){
                endPos = storagePoints.knotStartPosition_Y(indexChildKnot[i]) + ((storagePoints.knotHeight(indexChildKnot[i]) - storagePoints.knotHeight(indexChildKnot[i]) % 2) / 2);
            }
            else{
                endPos = storagePoints.knotStartPosition_Y(indexChildKnot[i]) - ((storagePoints.knotHeight(indexChildKnot[i]) - storagePoints.knotHeight(indexChildKnot[i]) % 2) / 2);
            }

            if(endPos > max){
                max = endPos;
            }
            if(endPos < min){
                min = endPos;
            }
        }

        int step = max - min;
        step = (step - step % 2) / 2;

        if(j == 0){
            storageCoord.endPosition_Y = storagePoints.knotStartPosition_Y(index) + ((storagePoints.knotHeight(index) - storagePoints.knotHeight(index) % 2) / 2);
        }
        else{
            if(storageCoord.startPosition_Y - step < min){
                storageCoord.endPosition_Y = min - 75;
            }
            else{
                storageCoord.endPosition_Y = max + 75;
            }
        }

        if(storageCoord.cornerEarth == 2){
            storageCoord.endPosition_X = storageCoord.startPosition_X + 150;
        }
        else{
            storageCoord.endPosition_X = storageCoord.startPosition_X - 150;
        }
    }

    delete [] indexChildKnot;
}



void ChoiceBuild::calculationNewPosition(int index){
    int posX1, posX2;
    int posY1, posY2;

    int posX11, posX21;
    int posY11, posY21;

    if(index > 0){
        int indexParent = storagePoints.knotIndexParentKnot(index);
        if(storagePoints.knotCountChildKnot(indexParent) > 1){
            posX1 = storagePoints.knotStartPosition_X(index);
            posY1 = storagePoints.knotStartPosition_Y(index);

            posX2 = posX1 + storagePoints.knotWidth(index);
            posY2 = posY1 + storagePoints.knotHeight(index);

            for(int i = 0; i < storagePoints.knotCountChildKnot(indexParent); ++i){
                posX11 = storagePoints.knotStartPosition_X(storagePoints.knotIndexChildKnot(indexParent, i));
                posY11 = storagePoints.knotStartPosition_Y(storagePoints.knotIndexChildKnot(indexParent, i));

                posX21 = posX11 + storagePoints.knotWidth(storagePoints.knotIndexChildKnot(indexParent, i));
                posY21 = posY11 + storagePoints.knotHeight(storagePoints.knotIndexChildKnot(indexParent, i));

                if(posX1 < posX11 && posX2 > posX11 && posY1 < posY11 && posY2 > posY11){
                    calculationShift(storagePoints.knotIndexChildKnot(indexParent, i), storagePoints.knotWidth(index) * 2, storagePoints.knotHeight(index) * 2, 1);
                }
                else if(posX1 < posX11 && posX2 > posX11 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storagePoints.knotIndexChildKnot(indexParent, i), storagePoints.knotWidth(index) * 2, storagePoints.knotHeight(index) * 2, 2);
                }
                else if(posX1 < posX21 && posX2 > posX21 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storagePoints.knotIndexChildKnot(indexParent, i), storagePoints.knotWidth(index) * 2, storagePoints.knotHeight(index) * 2, 3);
                }
                else if(posX1 < posX11 && posX2 > posX11 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storagePoints.knotIndexChildKnot(indexParent, i), storagePoints.knotWidth(index) * 2, storagePoints.knotHeight(index) * 2, 4);
                }
            }
        }
    }

    if(storagePoints.knotCountChildKnot(index) > 0){
        for(int i = 0; i < storagePoints.knotCountChildKnot(index); ++i){
            calculationNewPosition(storagePoints.knotIndexChildKnot(index, i));
        }
    }
}



void ChoiceBuild::calculationShift(int index, int width, int height, int shift){
    int startPosX = storagePoints.knotStartPosition_X(index);
    int startPosY = storagePoints.knotStartPosition_Y(index);

    if(shift == 1){
        startPosX += width;
        startPosY += height;
    }
    else if(shift == 2){
        startPosX -= width;
        startPosY += height;
    }
    else if(shift == 3){
        startPosX -= width;
        startPosY -= height;
    }
    else if (shift == 4){
        startPosX += width;
        startPosY -= height;
    }

    storagePoints.knotChange(index, startPosX, startPosY);

    int indexCurve = storagePoints.knotIndexCurve(index);
    storagePoints.curveChangeEndPosition(indexCurve, startPosX, startPosY);

    if(storagePoints.knotCountChildKnot(index) > 0){
        for(int i = 0; i < storagePoints.knotCountChildKnot(index); ++i){
            int indexCurve = storagePoints.knotIndexCurve(storagePoints.knotIndexChildKnot(index, i));

            if(shift == 1){
                storagePoints.curveChangeStartPosition(indexCurve, storagePoints.curveStartPosition_X(indexCurve) + width, storagePoints.curveStartPosition_Y(indexCurve) + height);
            }
            else if(shift == 2){
                storagePoints.curveChangeStartPosition(indexCurve, storagePoints.curveStartPosition_X(indexCurve) - width, storagePoints.curveStartPosition_Y(indexCurve) + height);
            }
            else if(shift == 3){
                storagePoints.curveChangeStartPosition(indexCurve, storagePoints.curveStartPosition_X(indexCurve) - width, storagePoints.curveStartPosition_Y(indexCurve) - height);
            }
            else{
                storagePoints.curveChangeStartPosition(indexCurve, storagePoints.curveStartPosition_X(indexCurve) + width, storagePoints.curveStartPosition_Y(indexCurve) - height);
            }

            calculationShift(storagePoints.knotIndexChildKnot(index, i), width, height, shift);
        }
    }
}
