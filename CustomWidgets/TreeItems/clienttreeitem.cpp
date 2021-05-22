#include "clienttreeitem.h"

ClientTreeItem::ClientTreeItem(client_model *client)
{
    this->client = client;
    setData(0, 0, QVariant(QString("client %1").arg(client->Work_id)));
}
