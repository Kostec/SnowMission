#include "questtreeitem.h"

QuestTreeItem::QuestTreeItem(Quest *quest)
{
    type = TreeItem::ItemType::QUEST;
    this->quest = quest;
    setData(0, 0, QVariant(QString("quest %1").arg(quest->id)));
    setData(1, 0, QVariant(Quest::QuestStateString()[quest->questState]));
    setData(2, 0, QVariant("Unit"));
    setData(3, 0, QVariant(quest->createTime));
    setData(4, 0, QVariant(quest->endTime));
}
