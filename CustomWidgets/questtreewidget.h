#ifndef QUESTTREEWIDGET_H
#define QUESTTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <Model/quest.h>

class QuestTreeWidget: public QTreeWidget
{
public:
    QuestTreeWidget();
    QTreeWidgetItem *clearNode;

private:
    QMap<Quest::QuestType, QTreeWidgetItem*> typeItemMap;
    QMap<Quest*, QTreeWidgetItem*> questItemMap;

public slots:
    void AddQuest(Quest *quest);
    void AddUnit();
    void QuestChangeState(Quest *quest, Quest::QuestState state);
};


#endif // QUESTTREEWIDGET_H
