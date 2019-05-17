#include "choicebuild.h"
#include <iostream>


ChoiceBuild::ChoiceBuild(){
}



void ChoiceBuild::calculation(int indexParentKnot){
    storageCoord.cornerEarth = calculationCornerEarth(indexParentKnot);
    calculationStartPosition(indexParentKnot);
    calculationEndPosition(indexParentKnot);
    //calculationNewPosition();
    calculationC1();
    calculationC2();
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



int ChoiceBuild::getC1_X(){
    return storageCoord.c1_X;
}



int ChoiceBuild::getC1_Y(){
    return storageCoord.c1_Y;
}



int ChoiceBuild::getC2_X(){
    return storageCoord.c2_X;
}



int ChoiceBuild::getC2_Y(){
    return storageCoord.c2_Y;
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

    for(int i = 0; i < storageObj.knotCountChildKnot(index); ++i){
        cornerEarth = storageObj.knotCornerEarth(storageObj.knotIndexChildKnot(index, i));

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

    cornerEarth = storageObj.knotCornerEarth(index);

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
            storageCoord.startPosition_Y = storageObj.knotStartPosition_Y(index);
        }
        else{
            step = storageObj.knotHeight(index);
            storageCoord.startPosition_Y = storageObj.knotStartPosition_Y(index) + step;
        }

        step = storageObj.knotWidth(index);
        storageCoord.startPosition_X = storageObj.knotStartPosition_X(index) + (step - step%2)/2;
    }
    else{
        if(storageCoord.cornerEarth == 4){
            storageCoord.startPosition_X = storageObj.knotStartPosition_X(index);
        }
        else{
            step = storageObj.knotWidth(index);
            storageCoord.startPosition_X = storageObj.knotStartPosition_X(index) + step;
        }

        step = storageObj.knotHeight(index);
        storageCoord.startPosition_Y = storageObj.knotStartPosition_Y(index) + (step - step%2)/2;
    }
}



void ChoiceBuild::calculationEndPosition(int index){

    int* indexChildKnot = new int[storageObj.knotCountChildKnot(index)];

    int j = 0;

    for(int i = 0; i < storageObj.knotCountChildKnot(index); ++i){
        if(storageCoord.cornerEarth == storageObj.knotCornerEarth(storageObj.knotIndexChildKnot(index, i))){
            indexChildKnot[j] = storageObj.knotIndexChildKnot(index, i);
            ++j;
        }
    }

    int max = 0, min = 300000;
    int endPos;

    if(storageCoord.cornerEarth == 1 || storageCoord.cornerEarth == 3){
        for(int i = 0; i < j; ++i){
            if(storageCoord.cornerEarth == 1){
                endPos = storageObj.knotStartPosition_X(indexChildKnot[i]) + ((storageObj.knotWidth(indexChildKnot[i]) - storageObj.knotWidth(indexChildKnot[i]) % 2) / 2);
            }
            else{
                endPos = storageObj.knotStartPosition_X(indexChildKnot[i]) - ((storageObj.knotWidth(indexChildKnot[i]) - storageObj.knotWidth(indexChildKnot[i]) % 2) / 2);
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
            storageCoord.endPosition_X = storageObj.knotStartPosition_X(index) + ((storageObj.knotWidth(index) - storageObj.knotWidth(index) % 2) / 2);
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
                endPos = storageObj.knotStartPosition_Y(indexChildKnot[i]) + ((storageObj.knotHeight(indexChildKnot[i]) - storageObj.knotHeight(indexChildKnot[i]) % 2) / 2);
            }
            else{
                endPos = storageObj.knotStartPosition_Y(indexChildKnot[i]) - ((storageObj.knotHeight(indexChildKnot[i]) - storageObj.knotHeight(indexChildKnot[i]) % 2) / 2);
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
            storageCoord.endPosition_Y = storageObj.knotStartPosition_Y(index) + ((storageObj.knotHeight(index) - storageObj.knotHeight(index) % 2) / 2);
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
        int indexParent = storageObj.knotIndexParentKnot(index);
        if(storageObj.knotCountChildKnot(indexParent) > 1){
            posX1 = storageObj.knotStartPosition_X(index);
            posY1 = storageObj.knotStartPosition_Y(index);

            posX2 = posX1 + storageObj.knotWidth(index);
            posY2 = posY1 + storageObj.knotHeight(index);

            for(int i = 0; i < storageObj.knotCountChildKnot(indexParent); ++i){
                posX11 = storageObj.knotStartPosition_X(storageObj.knotIndexChildKnot(indexParent, i));
                posY11 = storageObj.knotStartPosition_Y(storageObj.knotIndexChildKnot(indexParent, i));

                posX21 = posX11 + storageObj.knotWidth(storageObj.knotIndexChildKnot(indexParent, i));
                posY21 = posY11 + storageObj.knotHeight(storageObj.knotIndexChildKnot(indexParent, i));

                if(posX1 < posX11 && posX2 > posX11 && posY1 < posY11 && posY2 > posY11){
                    calculationShift(storageObj.knotIndexChildKnot(indexParent, i), storageObj.knotWidth(index) * 2, storageObj.knotHeight(index) * 2, 1);
                }
                else if(posX1 < posX11 && posX2 > posX11 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storageObj.knotIndexChildKnot(indexParent, i), storageObj.knotWidth(index) * 2, storageObj.knotHeight(index) * 2, 2);
                }
                else if(posX1 < posX21 && posX2 > posX21 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storageObj.knotIndexChildKnot(indexParent, i), storageObj.knotWidth(index) * 2, storageObj.knotHeight(index) * 2, 3);
                }
                else if(posX1 < posX11 && posX2 > posX11 && posY1 < posY21 && posY2 > posY21){
                    calculationShift(storageObj.knotIndexChildKnot(indexParent, i), storageObj.knotWidth(index) * 2, storageObj.knotHeight(index) * 2, 4);
                }
            }
        }
    }

    if(storageObj.knotCountChildKnot(index) > 0){
        for(int i = 0; i < storageObj.knotCountChildKnot(index); ++i){
            calculationNewPosition(storageObj.knotIndexChildKnot(index, i));
        }
    }
}



void ChoiceBuild::calculationShift(int index, int width, int height, int shift){
    int startPosX = storageObj.knotStartPosition_X(index);
    int startPosY = storageObj.knotStartPosition_Y(index);

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

    storageObj.knotChange(index, startPosX, startPosY);

    int indexCurve = storageObj.knotIndexCurve(index);
    storageObj.curveChangeEndPosition(indexCurve, startPosX, startPosY);

    std::cout << "index =" << index << std::endl;
    if(storageObj.knotCountChildKnot(index) > 0){
        for(int i = 0; i < storageObj.knotCountChildKnot(index); ++i){
            int indexCurve = storageObj.knotIndexCurve(storageObj.knotIndexChildKnot(index, i));

            if(shift == 1){
                storageObj.curveChangeStartPosition(indexCurve, storageObj.curveStartPosition_X(indexCurve) + width, storageObj.curveStartPosition_Y(indexCurve) + height);
            }
            else if(shift == 2){
                storageObj.curveChangeStartPosition(indexCurve, storageObj.curveStartPosition_X(indexCurve) - width, storageObj.curveStartPosition_Y(indexCurve) + height);
            }
            else if(shift == 3){
                storageObj.curveChangeStartPosition(indexCurve, storageObj.curveStartPosition_X(indexCurve) - width, storageObj.curveStartPosition_Y(indexCurve) - height);
            }
            else{
                storageObj.curveChangeStartPosition(indexCurve, storageObj.curveStartPosition_X(indexCurve) + width, storageObj.curveStartPosition_Y(indexCurve) - height);
            }

            calculationShift(storageObj.knotIndexChildKnot(index, i), width, height, shift);
        }
    }
}



void ChoiceBuild::calculationC1(){
    storageCoord.c1_X = storageCoord.startPosition_X + stepC;
    storageCoord.c1_Y = storageCoord.startPosition_Y - stepC;
}



void ChoiceBuild::calculationC2(){
    storageCoord.c2_X = storageCoord.endPosition_X - stepC;
    storageCoord.c2_Y = storageCoord.endPosition_Y + stepC;
}
