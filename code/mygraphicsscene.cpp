#include "mygraphicsscene.h"
#include "qgraphicsview.h"
#include <QDebug>

myGraphicsScene::myGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

}
void myGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QPointF scenePos = event->scenePos();
    qDebug()<<"mousePress at"<<event->pos()<<"scene"<<scenePos;
    QList<double> coords;
    coords << scenePos.x()<<scenePos.y();
    emit mouseSelection(coords);
}

