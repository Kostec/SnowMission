#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>

class MapView : public QGraphicsView
{
public:
    MapView();
    virtual void dropEvent(QDropEvent *event) override;
};

#endif // MAPVIEW_H
