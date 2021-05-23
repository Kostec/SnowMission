#include "select_model.h"
#include <QDebug>

Select_model::Select_model(QList<map_cell> cells, int map_pix_step)
{
    time_status = new QGraphicsSimpleTextItem(this);
    Cells = cells;
    map_step = map_pix_step;
    RectBuilder(cells);
    S = Cells.size()*map_pix_step*map_pix_step;
    id = countId++;
    clearning_timer.start(1000);
    clearning_timer.callOnTimeout([this]{clearningProcess();});
    qDebug() << "selectModel" << id;
}

void Select_model::RectBuilder(QList<map_cell> cells)
{
    if (cells.size()==0) return;

    QPoint topLeft = cells[0].pos;
    QPoint botRight = cells[0].pos;
    for (int i=1;i<cells.size();i++)
    {
        if (topLeft.x()>cells[i].pos.x()) topLeft.setX(cells[i].pos.x());
        if (topLeft.y()>cells[i].pos.y()) topLeft.setY(cells[i].pos.y());
        if (botRight.x()<cells[i].pos.x()) botRight.setX(cells[i].pos.x());
        if (botRight.y()<cells[i].pos.y()) botRight.setY(cells[i].pos.y());
    }
    fromMapRect = QRect(topLeft,botRight);
    this->setRect(QRectF(QPointF(topLeft.x()*map_step,topLeft.y()*map_step),QPointF(botRight.x()*map_step+map_step,botRight.y()*map_step+map_step)));
}

void Select_model::clearningProcess()
{
    S-=Power;
    if(S<0)
    {
        S = 0;
        Power = 0;
        time_status->hide();

        endTimer.setSingleShot(true);
        endTimer.start(10);
    }
    if(Power>0)
    {
        int sec_count = qRound(S/Power);
        QTime time = QTime(0, 0).addSecs(sec_count);
        QString s_time = time.toString("mm:ss");
        qDebug()<<"time to finish"<<s_time;
        time_status->setText(s_time);
        time_status->setFont(QFont("Bavaria", 25, 25));
        time_status->show();
        this->scene()->update();
        qDebug() << time_status->pos();
    }
}

void Select_model::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(QColor(117,174,232,120)));
    painter->drawRect(this->rect());
    painter->setPen(QPen(Qt::red));
    for (int i = 0; i<Cells.size();i++)
    {
        QPoint draw_point = Cells[i].pos - fromMapRect.topLeft();
        QPointF draw_pointF = QPointF(draw_point.x()*map_step,draw_point.y()*map_step)+this->rect().topLeft();
        painter->drawRect(QRectF(draw_pointF,draw_pointF+QPointF(map_step-1,map_step-1)));
    }
}
