#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

class myGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myGraphicsView(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent* pWheelEvent);

signals:

public slots:
};

#endif // MYGRAPHICSVIEW_H
