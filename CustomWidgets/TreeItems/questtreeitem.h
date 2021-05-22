#ifndef QUESTTREEITEM_H
#define QUESTTREEITEM_H

#include "CustomWidgets/TreeItems/treeitem.h"
#include "Models/quest.h"

class QuestTreeItem: public TreeItem
{
public:
    QuestTreeItem(Quest *quest);
    Quest *quest;
};

#endif // QUESTTREEITEM_H
