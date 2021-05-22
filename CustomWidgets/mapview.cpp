#include "mapview.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <Models/client_model.h>
#include <QByteArray>


MapView::MapView()
{

}

void MapView::dropEvent(QDropEvent *event)
{
    qDebug() << "Map drop event";
    uint clientId = event->mimeData()->property("client_id").toUInt();
    qDebug() << "drop clientId" << clientId;
    event->accept();
}

void MapView::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
    QVariant var = property("client_id");
}
