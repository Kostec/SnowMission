#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <QObject>
#include "AStar.hpp"
#include <iostream>
#include <QPoint>
#include <QSize>
#include "Models/map_cell.h"


class Path_finder : public QObject
{
    Q_OBJECT

public:
    explicit Path_finder(QVector<QVector<map_cell>> *map, QObject *parent = nullptr);
    AStar::Generator generator;
public slots:
    QList<QPoint> GeneratrPath(QPoint start, QPoint end);
signals:

};

#endif // PATH_FINDER_H
