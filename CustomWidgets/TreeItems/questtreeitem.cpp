#include "questtreeitem.h"

QuestTreeItem::QuestTreeItem(Quest *quest)
{
    type = TreeItem::ItemType::QUEST;
    this->quest = quest;
    setData(1, 0, QVariant(QString("Задача %1").arg(quest->id)));
    setData(2, 0, QVariant(Quest::QuestStateString()[quest->questState]));
    setData(3, 0, QVariant(quest->createTime));
//    setData(4, 0, QVariant("Unit"));
//    setData(4, 0, QVariant(quest->endTime));
    setExpanded(true);
}
