#ifndef STORAGEPOINTS_H
#define STORAGEPOINTS_H

#include <QString>
#include <QVector>


class StoragePoints
{
public:
    StoragePoints();

    //set knot
    void knotChange(int index, int startPos_X, int startPos_Y, int width, int height, int indexParentKnot, int cornerEarth);
    void knotChange(int index, int startPos_X, int startPos_Y);
    void knotChange(int index, int indexParentKnot);
    void knotChangeSize(int index, int width, int height);
    void knotChangeWidth(int index, int width);
    void knotChangeHeight(int index, int height);
    void knotChangeIndexChildKnot(int index, int indexChildKnotSelected, int indexChildKnotValue);
    void knotChangeCornerEarth(int index, int cornerEarth);
    void knotChangeStartPosition_X(int index, int startPosition_X);
    void knotChangeStartPosition_Y(int index, int startPosition_Y);
    void knotChangeIndexCurve(int index, int value);

    //get knot
    int knotStartPosition_X(int index);
    int knotStartPosition_Y(int index);
    int knotWidth(int index);
    int knotHeight(int index);
    int knotIndexParentKnot(int index);
    int knotIndexChildKnot(int index, int indexChildKnotSelected);
    int knotCountChildKnot(int index);
    int knotCornerEarth(int index);
    int knotIndexCurve(int index);

    //set curve
    void curveChange(int index, int indexParentKnot, int startPosX, int startPosY, int endPosX, int endPosY);
    void curveChange(int index, int indexParentKnot);
    void curveChangeStartPosition(int index, int startPosition_X, int startPosition_Y);
    void curveChangeEndPosition(int index, int endPosition_X, int endPosition_Y);
    void curveChangeEndPosition_X(int index, int endPosition_X);
    void curveChangeEndPosition_Y(int index, int endPosition_Y);

    //get curve
    int curveIndexParentKnot(int index);
    int curveStartPosition_X(int index);
    int curveStartPosition_Y(int index);
    int curveEndPosition_X(int index);
    int curveEndPosition_Y(int index);

    //set indexKnotNCurve
    void addKnot(int indexCurve);
    void changeKnot(int indexKnot, int indexCurve);

    //get indexKnotNCurve
    int getCurveIndex(int indexKnot);

    //set text
    void setText(int indexKnot, QString value);
    void popBackText(int indexKnot);

    //get text
    QString getText(int indexKnot);
    QString getAllText(int indexKnot);

private:
    struct knotStruct{
        int startPosition_X;
        int startPosition_Y;

        int width;
        int height;

        int indexCurve;

        int indexParentKnot = 0;
        int *indexChildKnot = new int[200];

        int countChildKnot = 0;

        //Обозначает с какой стороны присоединене этот узел к родительскому.
        //0 -> не имеет подключений.
        //От 1 до 4 соответсвуюе положению подключения по сторонам света С -> З (по часовой стрелке).
        //Пример, при значении равном 1:
        /*              ||
         * --------------------------
         * |    Какой-то текст      |
         * --------------------------
         */
        int cornerEarth = 0;

        QString text = "Введите текст";
        QString allText = "Введите текст";
    };

    struct curveBezierStruct{
        //Данное значение indexParentKnot отличается от такого же в knotStruct,
        //в данном случае родительским узлом является, то вместе, с которым создается данная кривая.
        int indexParentKnot;

        int startPosition_X;
        int startPosition_Y;
        int endPosition_X;
        int endPosition_Y;
    };

    static QVector<int> indexKnotNCurve;

    static knotStruct* knotStorage;
    static curveBezierStruct* curveStorage;
};

#endif // STORAGEPOINTS_H
