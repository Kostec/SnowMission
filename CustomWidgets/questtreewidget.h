#ifndef QUESTTREEWIDGET_H
#define QUESTTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <CustomWidgets/TreeItems/questtreeitem.h>
#include <CustomWidgets/TreeItems/clienttreeitem.h>
#include <Models/quest.h>
#include <Models/select_model.h>
#include <QObject>

class QuestTreeWidget: public QTreeWidget
{

public:
    QuestTreeWidget();
//    void dropEvent(QDropEvent *event) override;

    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void mouseMoveEvent( QMouseEvent *event ) override;

    void AddQuest(Quest *quest);

    Quest* AddQuest(Quest::QuestType type, int selectModelId);
    void RemoveQuestById(int id);
    QList<Select_model*>* selectModels;
    QList<client_model*>* client_list;

    QMap<uint, ClientTreeItem*> clientTree;
    QMap<int, QuestTreeItem*> questItems;

    void MoveClientToQuest(int clientId, int QuestId);
private:
    QMap<Quest::QuestType, QTreeWidgetItem*> typeItemMap;
    QMap<Quest*, QTreeWidgetItem*> questItemMap;

    QTreeWidgetItem units_item;

public slots:
    void QuestUpdate(Quest *quest);
    void QuestChangeState(Quest *quest, Quest::QuestState state);
    void AddClient(client_model *client);
    void CreateQuestInContainer(int idx);
};


#endif // QUESTTREEWIDGET_H
