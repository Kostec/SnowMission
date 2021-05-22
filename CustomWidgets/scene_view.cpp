#include "scene_view.h"

Scene_view::Scene_view()
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    map_item = new QGraphicsPixmapItem(QPixmap(":/Ikons/map.jpg"));
    scene->addItem(map_item);
    ViewPoint = map_item->boundingRect().center();
    this->centerOn(ViewPoint);
    generate_map();
}

void Scene_view::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>0)
    {
        this->scale(0.9,0.9);
        view_scale*=1.1;
    }
    else
    {
        this->scale(1.1,1.1);
        view_scale*=0.9;
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
    case Qt::RightButton:
    {
        mapDragStartPos = event->pos();
        move_event = true;
        break;
    }
    }
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
        QList<map_cell> selected_cells = MapSelectCells(select_zone);
//        QImage test = QImage(map_item->pixmap().toImage());
//        int counter =0;
//        for (int i=0;i<map_size.x() ;i++ ) {
//            for (int j=0;j<map_size.y() ;j++ )
//            {
//                for (int k = 0;k<selected_cells.size() ;k++ ) {
//                    if (QPoint(i,j)==selected_cells.at(k).pos)
//                    {
//                        for (int x = 0;x<map_pix_step ;x++ ) {
//                            test.setPixelColor(map_pix_step*i+x,map_pix_step*j,Qt::red);
//                            test.setPixelColor(map_pix_step*i+x,map_pix_step*j+map_pix_step-1,Qt::red);
//                            test.setPixelColor(map_pix_step*i,map_pix_step*j+x,Qt::red);
//                            test.setPixelColor(map_pix_step*i+map_pix_step-1,map_pix_step*j+x,Qt::red);
//                        }
//                        counter++;
//                    }

//                }
//            }
//        }
//        qDebug()<<"counter"<<counter;
//        test.save("test1.png");
        scene->removeItem(select_region);
        delete select_region;
        select_event = false;
        break;
    }
    case Qt::RightButton:
    {
        mapDragStartPos = QPoint();
        move_event = false;
        break;
    }
    }
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
    //    QImage test = road_map->copy();
    //    for (int i=0;i<map_size.x() ;i++ ) {
    //        for (int j=0;j<map_size.y() ;j++ )
    //        {
    //            if (!Map[j][i].plane_colision)
    //            {
    //                for (int x = 0;x<map_pix_step ;x++ ) {
    //                    test.setPixelColor(map_pix_step*i+x,map_pix_step*j,Qt::red);
    //                    test.setPixelColor(map_pix_step*i+x,map_pix_step*j+map_pix_step-1,Qt::red);
    //                    test.setPixelColor(map_pix_step*i,map_pix_step*j+x,Qt::red);
    //                    test.setPixelColor(map_pix_step*i+map_pix_step-1,map_pix_step*j+x,Qt::red);
    //                }

    //            }
    //        }
    //    }
    //    test.save("test.png");
}
