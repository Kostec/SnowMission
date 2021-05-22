#ifndef CLIENTTREEITEM_H
#define CLIENTTREEITEM_H

#include "CustomWidgets/TreeItems/treeitem.h"
#include "Models/client_model.h"

class ClientTreeItem : public TreeItem
{
public:
    ClientTreeItem(client_model *client);
    client_model *client;
};

#endif // CLIENTTREEITEM_H
