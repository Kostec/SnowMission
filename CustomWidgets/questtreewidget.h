#ifndef QUESTTREEWIDGET_H
#define QUESTTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <CustomWidgets/TreeItems/questtreeitem.h>
#include <CustomWidgets/TreeItems/clienttreeitem.h>
#include <Model/quest.h>

class QuestTreeWidget: public QTreeWidget
{
public:
    QuestTreeWidget();
//    void dropEvent(QDropEvent *event) override;

    QTreeWidgetItem *clearNode;
    QTreeWidgetItem *clientsNode;

    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void mouseMoveEvent( QMouseEvent *event ) override;

private:
    QMap<Quest::QuestType, QTreeWidgetItem*> typeItemMap;
    QMap<Quest*, QTreeWidgetItem*> questItemMap;

public slots:
    void AddQuest(Quest *quest);
    void QuestUpdate(Quest *quest);
    void QuestChangeState(Quest *quest, Quest::QuestState state);
    void AddClient(client_model *client);
};


#endif // QUESTTREEWIDGET_H
