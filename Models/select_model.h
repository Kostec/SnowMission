#ifndef SELECT_MODEL_H
#define SELECT_MODEL_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include "Models/map_cell.h"


class Select_model : public QGraphicsRectItem
{
public:
    Select_model(QList<map_cell> cells, int map_pix_step);

    QList<map_cell> Cells;
    int map_step;
    QRect fromMapRect;
    qreal S = 0;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
public slots:
    void RectBuilder(QList<map_cell> cells);
};

#endif // SELECT_MODEL_H
