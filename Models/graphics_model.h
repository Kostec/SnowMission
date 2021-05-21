#ifndef GRAPHICS_MODEL_H
#define GRAPHICS_MODEL_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPixmap>
#include <QPointF>

class Graphics_model : public QGraphicsItem
{
public:
    enum Unit_type
    {
        Truck = 1,
        Excavator,
        Rotary_loader,
        Brush_machine,
        Reagent_brush_machine,
        Plane
    };

    Graphics_model(int type, int id);

    QGraphicsPixmapItem icon_item;
    QGraphicsSimpleTextItem ID_item;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GRAPHICS_MODEL_H
