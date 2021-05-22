#include "path_finder.h"

Path_finder::Path_finder(QVector<QVector<map_cell>> *map, QObject *parent) : QObject(parent)
{
    QSize map_size = QSize(map->at(0).size(),map->size());
    generator.setWorldSize({map_size.width(), map_size.height()});
    generator.setHeuristic(AStar::Heuristic::euclidean);

    generator.setDiagonalMovement(true);
    for (int i = 0; i<map_size.width();i++)
        for(int j = 0; j<map_size.height(); j++)
            if (!map->at(j).at(i).road)
                generator.addCollision({i,j});



}

QList<QPoint> Path_finder::GeneratrPath(QPoint start, QPoint end)
{
    auto path = generator.findPath({start.x(),start.y()}, {end.x(),end.y()});
    QList<QPoint> rezult;
    for(auto& coordinate : path) {
        QPoint cell;
        cell = QPoint(coordinate.x,coordinate.y);
        rezult.append(cell);
    }
    return rezult;
}
