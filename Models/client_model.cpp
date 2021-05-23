#include "client_model.h"
#include "select_model.h"
#include "math/path_finder.h"
#include <QThread>

client_model::client_model(int type, int id,  QObject *parent) : QObject(parent)
{
    unit_ID = id;
    unit_Type = type;
    icon_item = new QGraphicsPixmapItem();
    ID_item = new QGraphicsSimpleTextItem(icon_item);
    switch (type) {
    case Unit_type::Truck:
    {
        icon_item->setPixmap(QPixmap(":/Ikons/Truck.png").scaled(70,50));
        break;
    }
    case Unit_type::Excavator:
    {
        icon_item->setPixmap(QPixmap(":/Ikons/Excavator.png").scaled(70,50));
        break;
    }
    case Unit_type::Brush_machine:
    {
        icon_item->setPixmap(QPixmap(":/Ikons/Brush_machine.png").scaled(70,50));
        break;
    }
    case Unit_type::Reagent_brush_machine:
    {
        icon_item->setPixmap(QPixmap(":/Ikons/Reagent_brush_machine.png").scaled(70,50));
        break;
    }
    case Unit_type::Rotary_loader:
    {
        icon_item->setPixmap(QPixmap(":/Ikons/Rotary_loader.png").scaled(70,50));
        break;
    }
    }

    icon_item->setPos(QPointF(-icon_item->pixmap().width()/2,-icon_item->pixmap().height()/2) + QPointF(Lalittude,Longituge));
    ID_item->setText(QString::number(id));
    ID_item->setPos(-ID_item->boundingRect().width()/2,-(icon_item->pixmap().height() + ID_item->boundingRect().height() + 5)/2);
    icon_item->show();
    ID_item->show();
    connect(&move_timer,SIGNAL(timeout()),this,SLOT(update()));
    //    socket = _socket;
    //    connect(socket,SIGNAL(readyRead()),this,SLOT(resive_Data()));
}

void client_model::finder_start( QVector<QVector<map_cell> > *Map)
{
    Finder = new Path_finder(Map);
    connect(this,SIGNAL(findePath(QPoint,QPoint)),Finder,SLOT(GeneratrPath(QPoint, QPoint)));
    connect(Finder,SIGNAL(newPath(QList<QPoint>)),this,SLOT(newPath(QList<QPoint>)));
    QThread *finder_thread = new QThread(this);
    Finder->moveToThread(finder_thread);
    finder_thread->start(QThread::TimeCriticalPriority);

}

void client_model::resive_Data()
{
    qDebug()<<"Resive data";
    while (socket->bytesAvailable() != 0)
    {
        // Начинаем транзакцию
        socket->startTransaction();
        // Ожидаем начало пакета
        QByteArray buffer = socket->readAll();
        //    qDebug()<<"получено сообщение";
        //    qDebug() << buffer;
        int index = buffer.indexOf(Start_SIGNATURE.toUtf8());

        if (index == -1) {
            qDebug() << "Начало пакета не найдено";
            // Начало пакета не найдено, по-этому подтверждаем чтение(чистим буфер) и выходим
            socket->commitTransaction();
            return;
        }
        // Отменяем чтение сигнатуры
        socket->rollbackTransaction();
        socket->startTransaction();
        // Пропускаем весь мусор, который идёт до начала пакета
        socket->read(index);
        // Подтверждаем чтение
        socket->commitTransaction();
        // Начинаем новую транзакцию
        socket->startTransaction();
        // Переходим в режим чтения
        // Читаем сигнатуру начала пакета
        socket->read(Start_SIGNATURE.size() - 1);

        // ID пакета
        int packet_id = readInt2();
        if (packet_id == -1) {
            qDebug("Не удалось прочесть ID пакета");
            socket->rollbackTransaction();
            return;
        }
        // Размер пакета
        int packetSize = readInt2();
        if (packetSize == -1) {
            qDebug("Не удалось прочесть размер пакета");
            socket->rollbackTransaction();
            return;
        }

        qDebug("ID = %d; Размер = %d", packet_id, packetSize);
        // Тело пакета
        QByteArray body = socket->read(packetSize);
        // Фактически тело пакета меньше запрошенного размера?
        if (body.size() < packetSize) {
            qDebug("Тело пакета получено не полностью. Откат транзакции...");

            socket->rollbackTransaction();
            return;
        }
        // Тело пакета получено полностью, можно подтверждать транзакцию
        socket->commitTransaction();
        switch ((Packet_id)packet_id) {
        case Packet_id::Telemetry:
        {
            telemetry_pars(body);
            break;
        }
        case Packet_id::Type:
        {
            type_pars(body);
            break;
        }
        }
    }
}

int client_model::readInt() {
    QByteArray bytes = socket->read(sizeof(int));
    if (bytes.size() != sizeof(int)) return -1;
    return *(int*)bytes.constData();
}
int client_model::readInt2() {
    QByteArray bytes = socket->read(sizeof(int));
    if (bytes.size() != sizeof(int)) return -1;
    int a = (bytes.at(0) & 0xFF) << 24;
    int b = (bytes.at(1) & 0xFF) << 16;
    int c = (bytes.at(2) & 0xFF) << 8;
    int d = bytes.at(3) & 0xFF;
    return (a | b | c | d);
}

void client_model::telemetry_pars(QByteArray body)
{
    Inform_packet1 packet;
    if (!packet.setBytes(body)) return;
    Status = packet.data_packet->status;
    Work_id = packet.data_packet->work_id;
    Velosity = packet.data_packet->velosity;
    Longituge = packet.data_packet->longituge;
    Lalittude = packet.data_packet->lalittude;
    Power = packet.data_packet->power;
}

void client_model::type_pars(QByteArray body)
{

}

void client_model::update()
{
    if(!move_event) return;
    this->icon_item->setPos(QPointF(Path.at(Path.size()-move_count-1).x()*map_pix_step-this->icon_item->pixmap().width()/2,
                                    Path.at(Path.size()-move_count-1).y()*map_pix_step-this->icon_item->pixmap().height()/2));
    move_count++;
    if (move_count == Path.size())
    {
        move_event = false;
        move_count = 0;
        move_timer.stop();

        QList<QGraphicsItem *> colides = this->icon_item->collidingItems();
        foreach (QGraphicsItem *item, colides)
        {
            Select_model *select_model = qgraphicsitem_cast<Select_model *>(item);
            if(select_model != nullptr)
            {
                this->Work_id = select_model->questId;
                select_model->Power+=this->Power;
            }
        }
    }
    emit scene_update();
}

void client_model::MoveTo(QPoint target)
{
    QPoint start;
    start = QPoint(this->icon_item->pos().x()/map_pix_step,this->icon_item->pos().y()/map_pix_step);
    emit findePath(start,target);

}
void client_model::newPath(QList<QPoint> arg)
{
    Path = arg;
    move_event = true;
    move_count = 0;
    QList<QGraphicsItem *> colides = this->icon_item->collidingItems();
    foreach (QGraphicsItem *item, colides)
    {
        Select_model *select_model = qgraphicsitem_cast<Select_model *>(item);
        if(select_model != nullptr)
        {
            this->Work_id = select_model->questId;
            select_model->Power-=this->Power;
        }
    }
    move_timer.start(100);
}
