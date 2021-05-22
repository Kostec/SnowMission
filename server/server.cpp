#include "server.h"

Server::Server()
{
    QString ipAddress= QHostAddress(QHostAddress::Any).toString();

    if (!this->listen(QHostAddress(ipAddress),5000)) {
        qDebug() << "Error create";
        return;
    }
    qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                .arg(this->serverAddress().toString()).arg(this->serverPort());
}

void Server::incomingConnection(qintptr descriptor)
{
    QTcpSocket *socket=new  QTcpSocket();

    if(!socket->setSocketDescriptor(descriptor))
    {
        qDebug() << "Bad socket or descriptor";
        delete socket;
        return;
    }
    addPendingConnection(socket);
    qDebug() << "Incoming Connection on server from " + socket->peerAddress().toString();
    client_model *client = new client_model(socket);
    client->unit_ID = Id_counter;
    Id_counter++;
    emit new_client(client);
}
