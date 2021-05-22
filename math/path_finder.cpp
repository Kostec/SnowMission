#include "path_finder.h"

Path_finder::Path_finder(QVector<QVector<map_cell>> *map, QObject *parent) : QObject(parent)
{
    AStar::Generator generator;
    QSize map_size = QSize(map->at(0).size(),map->size());
    generator.setWorldSize({map_size.width(), map_size.height()});
    generator.setHeuristic(AStar::Heuristic::euclidean);

    generator.setDiagonalMovement(true);
    for (int i = 0; i<map_size.width();i++)
        for(int j = 0; j<map_size.height(); j++)
            if (!map->at(j).at(i).road)
                generator.addCollision({i,j});


    std::cout << "Generate path ... \n";
    auto path = generator.findPath({0, 0}, {20, 20});

    for(auto& coordinate : path) {
        std::cout << coordinate.x << " " << coordinate.y << "\n";
    }
}
