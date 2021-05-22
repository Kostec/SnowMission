#include "server.h"
#include <QRandomGenerator>

Server::Server()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address() /*&& QNetworkInterface::allInterfaces()[i].name()!="ethernet_32769"*/) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (!ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    if (!this->listen(QHostAddress(ipAddress),50000)) {
        qDebug() << "Error create";
        return;
    }
    qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                .arg(this->serverAddress().toString()).arg(this->serverPort());
}

void Server::spawn(int count)
{
    QRandomGenerator generator;
        for (int i = 0;i<count;i++)
        {
            client_model *client = new client_model(QRandomGenerator::global()->bounded(1,6),Id_counter);
            client->Lalittude = QRandomGenerator::global()->bounded(200,12000);
            client->Longituge = QRandomGenerator::global()->bounded(200,5000);
            client->icon_item->setPos(client->Lalittude,client->Longituge);
            Id_counter++;
            emit new_client(client);
        }
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
}
