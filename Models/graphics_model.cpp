#include "graphics_model.h"

Graphics_model::Graphics_model(int type, int id)
{
    switch (type) {
    case Unit_type::Truck:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Truck.png"));
        break;
    }
    case Unit_type::Excavator:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Excavator.png"));
        break;
    }
    case Unit_type::Brush_machine:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Brush_machine.png"));
        break;
    }
    case Unit_type::Reagent_brush_machine:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Reagent_brush_machine.png"));
        break;
    }
    case Unit_type::Rotary_loader:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Rotary_loader.png"));
        break;
    }
    case Unit_type::Plane:
    {
        icon_item.setPixmap(QPixmap(":/Ikons/Plane.png"));
        icon_item.setRotation(45);
        break;
    }
    }
    icon_item.setPos(QPointF(-icon_item.pixmap().width()/2,-icon_item.pixmap().height()/2));
    ID_item.setText(QString::number(id));
    ID_item.setPos(-ID_item.boundingRect().width()/2,-(icon_item.pixmap().height() + ID_item.boundingRect().height() + 5)/2);
}

QRectF Graphics_model::boundingRect() const
{
    return icon_item.boundingRect().united(ID_item.boundingRect());
}

void Graphics_model::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
