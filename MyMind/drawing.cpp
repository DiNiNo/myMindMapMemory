#include "drawing.h"

Drawing::Drawing(){

}



QPainterPath& Drawing::drawing(int &startPosition_X, int &startPosition_Y, int &endPosition_X, int &endPosition_Y, int &c1_X, int &c1_Y, int &c2_X, int &c2_Y, int &width, int &height){
    QVector<QPainter> vecPainter;

    QPointF c1;
    c1.setX(c1_X);
    c1.setY(c1_Y);

    QPointF c2;
    c2.setX(c2_X);
    c2.setY(c2_Y);

    QPointF endPosition;
    endPosition.setX(endPosition_X);
    endPosition.setY(endPosition_Y);

    //QPainterPath path;
    path.moveTo(startPosition_X, startPosition_Y);
    path.cubicTo(c1,c2,endPosition);

    return path;

    /*QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(15);
    pen.setColor(Qt::black);

    vecPainter.push_back(drawingBezier(path, pen));

    int startPosositionKnot_X = endPosition_X - (height - height % 2)/2;

    QRectF rectangle(startPosositionKnot_X, endPosition_Y, width, height);

    vecPainter.push_back(drawingKnot(rectangle, pen));

    return vecPainter;*/
}



/*QPainter& Drawing::drawingBezier(QPainterPath &path, QPen &pen){
    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.scale(0.1, 0.1);
    painter.setPen(pen);
    painter.drawPath(path);

    return painter;
}



QPainter& Drawing::drawingKnot(QRectF &rectangle, QPen &pen){
    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);
    painter.drawEllipse(rectangle);

    return painter;
}*/



Drawing::~Drawing(){}
