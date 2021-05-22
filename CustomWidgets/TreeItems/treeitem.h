#ifndef TREEITEM_H
#define TREEITEM_H

#include <QTreeWidgetItem>

class TreeItem: public QTreeWidgetItem
{
public:
    enum ItemType{ NONE, USER, QUEST };

    ItemType type = NONE;
    TreeItem();
};

#endif // TREEITEM_H
