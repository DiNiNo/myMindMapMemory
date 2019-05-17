#ifndef KNOTSTRUCT_H
#define KNOTSTRUCT_H


class KnotStruct
{
public:
    KnotStruct();

    int startPosition_X;
    int startPosition_Y;

    int width;
    int height;

    int indexParentKnot;
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
};

#endif // KNOTSTRUCT_H
