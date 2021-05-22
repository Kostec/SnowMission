#include "client_model.h"

client_model::client_model(QTcpSocket *_socket, QObject *parent) : QObject(parent)
{
    socket = _socket;
//    connect(socket,SIGNAL(readyRead()),SLOT(resive_Data()));
}

void client_model::resive_Data()
{
    if (socket->bytesAvailable() == 0) return;
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
    int packet_id = readInt();
    if (packet_id == -1) {
        qDebug("Не удалось прочесть ID пакета");
        socket->rollbackTransaction();
        return;
    }
    // Размер пакета
    int packetSize = readInt();
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
    switch (packet_id) {
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

int client_model::readInt() {
    QByteArray bytes = socket->read(sizeof(int));
    if (bytes.size() != sizeof(int)) return -1;
    return *(int*)bytes.constData();
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
    type_packet packet;
    if (!packet.setBytes(body)) return;
    unit_Type = packet.data_packet->type;

    if (view_item != nullptr) return;
    view_item = new Graphics_model(unit_Type,unit_ID);
}
