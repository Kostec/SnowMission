#include "select_model.h"

Select_model::Select_model(QList<map_cell> cells, int map_pix_step)
{
    Cells = cells;
    map_step = map_pix_step;
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

}

void Select_model::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(this->rect());
}
