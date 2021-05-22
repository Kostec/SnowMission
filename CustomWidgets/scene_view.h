#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QtDebug>
#include <QWheelEvent>
#include <QImage>
#include <QPoint>
#include <QPointF>
#include <QVector>
#include <QMouseEvent>

struct map_cell
{
    QPoint pos;
    bool road = false;
    bool plane_colision = false;
    bool unit_colision = false;
};

class Scene_view : public QGraphicsView
{
    Q_OBJECT
public:
    Scene_view();
    QGraphicsScene *scene;
    QGraphicsPixmapItem *map_item;
    QGraphicsRectItem *select_region;

    QPoint map_size;
    QVector<QVector<map_cell>> Map;
    QPoint mapDragStartPos;
    QPointF ViewPoint = QPoint();

    QPointF scene_firs_point;

    bool move_event = false;
    bool select_event = false;
    qreal view_scale = 1.0;

    int map_pix_step = 10;

    // QWidget interface
public slots:
    void generate_map();

    QList<map_cell> MapSelectCells(QRectF rect);
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // SCENE_VIEW_H
