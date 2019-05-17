#ifndef CHOICEBUILD_H
#define CHOICEBUILD_H

#include "storagepoints.h"


class ChoiceBuild
{
public:
    ChoiceBuild();

    void calculation(int indexParentKnot);

    int getStartPosition_X();
    int getStartPosition_Y();
    int getEndPosition_X();
    int getEndPosition_Y();
    int getC1_X();
    int getC1_Y();
    int getC2_X();
    int getC2_Y();
    int getCornerEarth();
    void calculationNewPosition(int index);

private:
    StoragePoints storageObj;

    int stepC = 25;

    struct storageNewCoordinate{
        int startPosition_X;
        int startPosition_Y;
        int endPosition_X;
        int endPosition_Y;

        int c1_X;
        int c1_Y;
        int c2_X;
        int c2_Y;

        int cornerEarth;
    };

    storageNewCoordinate storageCoord;

    int calculationCornerEarth(int index);
    void calculationStartPosition(int index);
    void calculationEndPosition(int index);
    void calculationShift(int index, int width, int height, int shift);
    void calculationC1();
    void calculationC2();
};

#endif // CHOICEBUILD_H
