#ifndef CLIENTTREEITEM_H
#define CLIENTTREEITEM_H

#include <QTreeWidgetItem>

#include <Models/client_model.h>

class ClientTreeItem : public QTreeWidgetItem
{
public:
    ClientTreeItem(client_model *client);
    client_model *client;
};

#endif // CLIENTTREEITEM_H
