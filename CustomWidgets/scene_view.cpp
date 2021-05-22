#include "scene_view.h"

#include <CustomWidgets/TreeItems/treeitem.h>
#include <QRandomGenerator>

#include <QMenu>

Scene_view::Scene_view()
{

    scene = new QGraphicsScene(this);
    this->setScene(scene);
    map_item = new QGraphicsPixmapItem(QPixmap(":/Ikons/map.jpg"));
    scene->addItem(map_item);
    ViewPoint = map_item->boundingRect().center();
    this->centerOn(ViewPoint);
    generate_map();
    finder = new Path_finder(&Map);

    //    setAcceptDrops(true);
}

void Scene_view::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>0)
    {
        this->scale(0.9,0.9);
        view_scale*=1.05;
    }
    else
    {
        this->scale(1.1,1.1);
        view_scale*=0.95;
    }
}

void Scene_view::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
    {
        scene_firs_point = this->mapToScene(event->pos());
        select_region = new QGraphicsRectItem(QRectF(scene_firs_point,QSizeF(1,1)));
        select_region->setBrush(QBrush(QColor(117,174,232,120)));
        scene->addItem(select_region);
        select_event = true;
        select_region->show();
        scene->update();
        break;
    }
    case Qt::MiddleButton:
    {
        mapDragStartPos = event->pos();
        move_event = true;
        break;
    }
    case Qt::RightButton:
    {

        QPointF scene_point = this->mapToScene(event->pos());


        QList<QGraphicsItem*> items = scene->items(scene_point);

        foreach(QGraphicsItem* item, items)
        {
            Select_model* model = qgraphicsitem_cast<Select_model*>(item);
            if (model != nullptr)
            {
                QMenu* menu = new QMenu();
                menu->addAction("Уборка", this, [this, model]{ emit createQuest(Quest::Clear, model->id); });
                menu->addAction("Проверка", this, [this, model]{ emit createQuest(Quest::Visit, model->id); });
                menu->addAction("Вывоз снега", this, [this, model]{ emit createQuest(Quest::Overflow, model->id); });
                menu->addAction("Удалить", this, [this, model]
                {
                    this->scene->removeItem(model);
                    selectModels.removeAll(model);
                    emit removeQuest(model->questId);
                });
                menu->exec(cursor().pos());
                break;
            }
            else
            {
                QPoint point = QPoint(qRound(scene_point.x()/map_pix_step),qRound(scene_point.y()/map_pix_step));
                if(Map[point.y()][point.x()].road)
                    for (int i = 0;i<client_list.size() ; i++ )
                    {
                        client_model *client = client_list.at(i);
                        client->MoveTo(QPoint(qRound(scene_point.x()/map_pix_step),qRound(scene_point.y()/map_pix_step)));
                    }
            }
        }
        break;
    }
    }

}


Quest *Scene_view::CreateQuest(Quest::QuestType type){
    Quest *quest = new Quest();
    quest->questType = type;
}

void Scene_view::mouseMoveEvent(QMouseEvent *event)
{
    if (move_event)
    {
        QPoint delta = event->pos() - mapDragStartPos;
        ViewPoint = ViewPoint - delta * view_scale;
        this->centerOn(ViewPoint);
        mapDragStartPos = event->pos();
    }
    if (select_event)
    {
        QPointF scene_second_point = this->mapToScene(event->pos());
        select_region->setRect(QRectF(scene_firs_point,scene_second_point));
        scene->update();
    }
}

void Scene_view::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
    {
        QRectF select_zone = select_region->boundingRect();
        QList<map_cell> selected_cells = MapSelectCells(select_zone.normalized());

        Select_model *new_select_item = new Select_model(selected_cells,map_pix_step);
        scene->addItem(new_select_item);
        scene->removeItem(select_region);
        delete select_region;
        select_event = false;

        selectModels.append(new_select_item);
        break;
    }
    case Qt::MiddleButton:
    {
        mapDragStartPos = QPoint();
        move_event = false;
        break;
    }
    }
}

void Scene_view::dragMoveEvent(QDragMoveEvent *event)
{
    QVariant variant (event->mimeData()->property("type_item"));
    if (variant.isValid())
    {
        if ((TreeItem::ItemType::USER) == variant.toInt())
        {
            variant = event->mimeData()->property("client_id");
            if (!variant.isValid())
            {
                event->ignore();
                return;
            }
            uint client_id = variant.toInt();
            qDebug() << "client_id" << client_id;
            event->accept();
        }
    }
}

void Scene_view::mouseDoubleClickEvent(QMouseEvent *event)
{

}

QList<map_cell> Scene_view::MapSelectCells(QRectF rect)
{
    QList<map_cell> rezult;
    QPoint top_left_point = QPoint(qRound(rect.topLeft().x())/map_pix_step,qRound(rect.topLeft().y())/map_pix_step);
    QPoint bot_rigth_point = QPoint(qRound(rect.bottomRight().x())/map_pix_step,qRound(rect.bottomRight().y())/map_pix_step);
    for (int j=top_left_point.x();j<=bot_rigth_point.x() ;j++ ) {
        for (int i=top_left_point.y();i<=bot_rigth_point.y() ;i++ ) {
            if (Map[i][j].road) rezult.append(Map[i][j]);
        }
    }
    return rezult;
}

void Scene_view::generate_map()
{
    QImage *road_map = new QImage(":/Ikons/map_road.jpg");
    map_size = QPoint(road_map->width()/map_pix_step,road_map->height()/map_pix_step);
    Map.resize(map_size.y());
    for (int i=0;i<Map.size() ;i++ ) {
        Map[i].resize(map_size.x());
    }

    QColor green_color(218,248,188);
    QColor road_color(160,160,160);
    QColor building_color(255,191,129);

    for (int i=0;i<map_size.x() ;i++ ) {
        for (int j=0;j<map_size.y() ;j++ )
        {
            Map[j][i].pos = QPoint(i,j);
            QColor color = road_map->pixelColor(map_pix_step*i+map_pix_step/2,map_pix_step*j+map_pix_step/2);
            if ((color.red()>=0.95*green_color.red())&&(color.red()<=1.05*green_color.red())&&
                    (color.green()>=0.95*green_color.green())&&(color.green()<=1.05*green_color.green())&&
                    (color.blue()>=0.95*green_color.blue())&&(color.blue()<=1.05*green_color.blue()))
            {
                Map[j][i].plane_colision = true;
                Map[j][i].unit_colision = true;
            }

            if ((color.red()>=0.95*building_color.red())&&(color.red()<=1.05*building_color.red())&&
                    (color.green()>=0.95*building_color.green())&&(color.green()<=1.05*building_color.green())&&
                    (color.blue()>=0.95*building_color.blue())&&(color.blue()<=1.05*building_color.blue()))
            {
                Map[j][i].plane_colision = true;
                Map[j][i].unit_colision = true;
            }

            if ((color.red()>=0.95*road_color.red())&&(color.red()<=1.05*road_color.red())&&
                    (color.green()>=0.95*road_color.green())&&(color.green()<=1.05*road_color.green())&&
                    (color.blue()>=0.95*road_color.blue())&&(color.blue()<=1.05*road_color.blue()))
            {
                Map[j][i].plane_colision = false;
                Map[j][i].unit_colision = false;
                Map[j][i].road = true;
            }
        }
    }
}

void Scene_view::new_unit(client_model *client)
{
    connect(client,SIGNAL(scene_update()),scene,SLOT(update()));
    client->finder_start(&Map);
    scene->addItem(client->icon_item);
    client->icon_item->show();

    client_list.append(client);
    QPoint point = QPoint(qRound(client->icon_item->pos().x()/map_pix_step),qRound(client->icon_item->pos().y()/map_pix_step));
    while (!Map[point.y()][point.x()].road)
    {

        client->Lalittude = QRandomGenerator::global()->bounded(200,12000);
        client->Longituge = QRandomGenerator::global()->bounded(200,5000);
        point = QPoint(client->Lalittude/map_pix_step,client->Longituge/map_pix_step);
    }
    client->icon_item->setPos(client->Lalittude-client->icon_item->pixmap().width()/2,client->Longituge-client->icon_item->pixmap().height()/2);
    emit addClientToTree(client);
    scene->update();

}
void Scene_view::dropEvent(QDropEvent *event)
{
    qDebug() << "Map drop event";
    uint clientId = event->mimeData()->property("client_id").toUInt();
    qDebug() << "drop clientId" << clientId;

    QList<QGraphicsItem*> items = scene->items(mapToScene(event->pos()));
    foreach(QGraphicsItem *item, items)
    {
        Select_model *model = qgraphicsitem_cast<Select_model *>(item);
        if (model != nullptr)
        {
            foreach(client_model *client, client_list)
            {
                if (client->unit_ID == clientId)
                {
                    client->MoveTo(QPoint(qRound(mapToScene(event->pos()).x()/map_pix_step),
                                          qRound(mapToScene(event->pos()).y()/map_pix_step)));
                    break;
                }
            }
            break;
        }
    }


    event->accept();
}

void Scene_view::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
    QVariant var = property("client_id");
}
