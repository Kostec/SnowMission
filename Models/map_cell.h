#ifndef MAP_CELL_H
#define MAP_CELL_H
#include <QPoint>
struct map_cell
{
    QPoint pos;
    bool road = false;
    bool plane_colision = false;
    bool unit_colision = false;
};
#endif // MAP_CELL_H
