#include "select_model.h"

Select_model::Select_model(QList<map_cell> cells, int map_pix_step)
{
    Cells = cells;
    map_step = map_pix_step;
    RectBuilder(cells);
}

void Select_model::RectBuilder(QList<map_cell> cells)
{
    if (cells.size()==0) return;

    QPoint topLeft = cells[0].pos;
    QPoint botRight = cells[0].pos;
    for (int i=1;i<cells.size();i++)
    {
        if (topLeft.x()>cells[i].pos.x()) topLeft.setX(cells[i].pos.x());
        if (topLeft.y()>cells[i].pos.y()) topLeft.setY(cells[i].pos.y());
        if (botRight.x()<cells[i].pos.x()) botRight.setX(cells[i].pos.x());
        if (botRight.y()<cells[i].pos.y()) botRight.setY(cells[i].pos.y());
    }
    fromMapRect = QRect(topLeft,botRight);
    this->setRect(QRectF(QPointF(topLeft.x()*map_step,topLeft.y()*map_step),QPointF(botRight.x()*map_step+map_step,botRight.y()*map_step+map_step)));
}

void Select_model::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(QColor(117,174,232,120)));
    painter->drawRect(this->rect());
    painter->setPen(QPen(Qt::red));
    for (int i = 0; i<Cells.size();i++)
    {
        QPoint draw_point = Cells[i].pos - fromMapRect.topLeft();
        QPointF draw_pointF = QPointF(draw_point.x()*map_step,draw_point.y()*map_step)+this->rect().topLeft();
        painter->drawRect(QRectF(draw_pointF,draw_pointF+QPointF(map_step-1,map_step-1)));
    }
}
