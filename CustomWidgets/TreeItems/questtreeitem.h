#ifndef QUESTTREEITEM_H
#define QUESTTREEITEM_H

#include <QTreeWidgetItem>
#include "Models/quest.h"

class QuestTreeItem : public QTreeWidgetItem
{
public:
    QuestTreeItem(Quest *quest);
    Quest *quest;
};

#endif // QUESTTREEITEM_H
