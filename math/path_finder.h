#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <QObject>
#include "AStar.hpp"
#include <iostream>
#include <QPoint>
#include <QSize>

struct map_cell
{
    QPoint pos;
    bool road = false;
    bool plane_colision = false;
    bool unit_colision = false;
};


class Path_finder : public QObject
{
    Q_OBJECT
public:
    explicit Path_finder(QVector<QVector<map_cell>> *map, QObject *parent = nullptr);

signals:

};

#endif // PATH_FINDER_H
