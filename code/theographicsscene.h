#ifndef THEOGRAPHICSSCENE_H
#define THEOGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class theoGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit theoGraphicsScene(QObject *parent = 0);

};

#endif // THEOGRAPHICSSCENE_H
