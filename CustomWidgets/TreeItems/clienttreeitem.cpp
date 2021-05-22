#include "clienttreeitem.h"

ClientTreeItem::ClientTreeItem(client_model *client)
{
    type = TreeItem::ItemType::USER;
    this->client = client;
    setData(1, 0, QVariant(QString("client %1").arg(client->unit_ID)));
    QPixmap icon_item;
    switch (client->unit_Type) {
    case client_model::Unit_type::Truck:
    {
        icon_item=(QPixmap(":/Ikons/Truck.png").scaled(70,50));
        break;
    }
    case client_model::Unit_type::Excavator:
    {
        icon_item=(QPixmap(":/Ikons/Excavator.png").scaled(70,50));
        break;
    }
    case client_model::Unit_type::Brush_machine:
    {
        icon_item=(QPixmap(":/Ikons/Brush_machine.png").scaled(70,50));
        break;
    }
    case client_model::Unit_type::Reagent_brush_machine:
    {
        icon_item=(QPixmap(":/Ikons/Reagent_brush_machine.png").scaled(70,50));
        break;
    }
    case client_model::Unit_type::Rotary_loader:
    {
        icon_item=(QPixmap(":/Ikons/Rotary_loader.png").scaled(70,50));
        break;
    }
    }
    setIcon(0,icon_item);
}
