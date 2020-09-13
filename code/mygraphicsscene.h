#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QList>
#include <QWheelEvent>

class myGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myGraphicsScene(QObject *parent = nullptr);

signals:
    void mouseSelection(QList<double>);

private:
    QPointF aPoint;

public slots:

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void wheelEvent(QWheelEvent* event);
};

#endif // MYGRAPHICSSCENE_H
