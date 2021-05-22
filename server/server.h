#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>
#include <QtNetwork>
#include "math/path_finder.h"
#include "Models/client_model.h"


class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();

    Path_finder *finder;
    int Id_counter = 1;
public slots:

    void spawn(int count);

signals:
    void new_client(client_model *client);

protected:
    void incomingConnection(qintptr descriptor) override;
};

#endif // SERVER_H
