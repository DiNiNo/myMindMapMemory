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
    int getCornerEarth();
    void calculationNewPosition(int index);

private:
    StoragePoints storagePoints;

    struct storageNewCoordinate{
        int startPosition_X;
        int startPosition_Y;

        int endPosition_X;
        int endPosition_Y;

        int cornerEarth;
    };

    storageNewCoordinate storageCoord;

    int calculationCornerEarth(int index);
    void calculationStartPosition(int index);
    void calculationEndPosition(int index);
    void calculationShift(int index, int width, int height, int shift);
};

#endif // CHOICEBUILD_H
