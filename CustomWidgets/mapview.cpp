#include "mapview.h"
#include <QDebug>

MapView::MapView()
{

}

void MapView::dropEvent(QDropEvent *event)
{
    qDebug() << "Map drop event";
}
