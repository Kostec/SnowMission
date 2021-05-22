#ifndef CLIENT_MODEL_H
#define CLIENT_MODEL_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPixmap>
#include <QPointF>
#include "server/packets/inform_packet1.h"
#include "server/packets/type_packet.h"
#include "graphics_model.h"
#include <QTimer>
#include "math/path_finder.h"
#include "Models/map_cell.h"

class client_model : public QObject
{
    Q_OBJECT
public:

    enum Packet_id
    {
        Telemetry = 1,
        Type
    };
    enum Unit_status
    {
        UnActive = 0,
        Working,
        Moving
    };
    enum Unit_type
    {
        Truck = 1,
        Excavator,
        Rotary_loader,
        Brush_machine,
        Reagent_brush_machine
    };

    explicit client_model(int type, int id, Path_finder *finder = nullptr, QObject *parent = nullptr);

    QTcpSocket *socket = nullptr;
    QGraphicsPixmapItem *icon_item;
    QGraphicsSimpleTextItem *ID_item;
    Path_finder *Finder;

    QString Start_SIGNATURE = "[START]";

    uint unit_Type = 0;
    uint unit_ID = 0;

    uint Status = Unit_status::UnActive;
    uint Work_id = 0;

    float Velosity = 0;
    float Longituge = 0;
    float Lalittude = 0;

    float Power = 0;
    int map_pix_step = 15;
    bool move_event = false;
    QTimer move_timer;
    QList<QPoint> Path;
    int move_count = 0;

public slots:
    void resive_Data();
    void telemetry_pars(QByteArray body);
    void type_pars(QByteArray body);
    void update();
    void MoveTo(QPoint target);
signals:
    void scene_update();

private slots:
    int readInt();
    int readInt2();
};

#endif // CLIENT_MODEL_H
