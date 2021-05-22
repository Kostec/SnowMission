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
#include "Models/select_model.h"
#include "Models/client_model.h"
#include <QMimeData>
#include "math/path_finder.h"
#include <Models/quest.h>

class Scene_view : public QGraphicsView
{
    Q_OBJECT
public:
    Scene_view();
    QGraphicsScene *scene;
    QGraphicsPixmapItem *map_item;
    QGraphicsRectItem *select_region;
    Path_finder *finder;
    QPoint map_size;
    QVector<QVector<map_cell>> Map;
    QPoint mapDragStartPos;
    QPointF ViewPoint = QPoint();

    QPointF scene_firs_point;

    bool move_event = false;
    bool select_event = false;
    qreal view_scale = 1.0;

    int map_pix_step = 30;
    QList<client_model*> client_list;
    QList<Select_model*> selectModels;

    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    // QWidget interface
    Quest *CreateQuest(Quest::QuestType type);

public slots:
    void generate_map();
    void new_unit(client_model *client);

    QList<map_cell> MapSelectCells(QRectF rect);
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void createQuest(Quest::QuestType, int clientModelId);
    void removeQuest(int questId);
    void addClientToTree(client_model* client);
    void moveClientToSelect(int clientId, int questId);

};

#endif // SCENE_VIEW_H
