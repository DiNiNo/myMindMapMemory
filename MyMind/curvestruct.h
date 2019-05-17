#ifndef CURVESTRUCT_H
#define CURVESTRUCT_H


class CurveStruct
{
public:
    CurveStruct();

    //Данное заначение indexParentKnot отличается от такого же в knotStruct,
    //в данном случае родительским узлом является, то вместе, с которым создается данная кривая.
    int indexParentKnot;

    int startPosition_X;
    int startPosition_Y;
    int endPosition_X;
    int endPosition_Y;

    int c1_X;
    int c1_Y;
    int c2_X;
    int c2_Y;
};

#endif // CURVESTRUCT_H
