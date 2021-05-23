#ifndef SELECT_MODEL_H
#define SELECT_MODEL_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include "Models/map_cell.h"
#include <QTime>
#include <QTimer>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>


class Select_model : public QGraphicsRectItem
{
public:
    Select_model(QList<map_cell> cells, int map_pix_step);

    uint id;
    int questId;

    QList<map_cell> Cells;
    int map_step;
    QRect fromMapRect;
    qreal S = 0;
    qreal Power = 0;

    QTimer clearning_timer;
    QGraphicsSimpleTextItem *time_status;

    QTimer endTimer;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
public slots:
    void RectBuilder(QList<map_cell> cells);
    void clearningProcess();
private:
    static inline uint countId = 0;
};

#endif // SELECT_MODEL_H
