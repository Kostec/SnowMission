#include "questtreewidget.h"
#include <QDataStream>
#include <QDebug>
#include <QDrag>
#include <QDragLeaveEvent>
#include <QMimeData>

QuestTreeWidget::QuestTreeWidget()
{

    setColumnCount(5);
    QStringList headerList;
    headerList.append("Тип");
    headerList.append("Название");
    headerList.append("Состояние");
    headerList.append("Дата создание");
    headerList.append("Дата завершения");
    setHeaderLabels(headerList);

    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    units_item.setData(0,0,QVariant("Units"));
    addTopLevelItem(&units_item);

    setSelectionMode(QAbstractItemView::MultiSelection);
}

void QuestTreeWidget::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void QuestTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (selectedItems().count() < 1) return;
        qDebug() << "selected drag items count " << selectedItems().count();

        foreach(QTreeWidgetItem* item, selectedItems())
        {
            TreeItem *treeItem = static_cast<TreeItem*>(item);
            if(!treeItem) return;

            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setProperty("type_item", QVariant(treeItem->type));
            mimeData->setProperty("client_id", QVariant(static_cast<ClientTreeItem*>(treeItem)->client->unit_ID));
            drag->setMimeData(mimeData);

            item->setSelected(false);

            event->accept();

            Qt::DropAction result = drag->exec( Qt::MoveAction );
            qDebug() << "Drop action result: " << result;
        }
    }
}

void QuestTreeWidget::AddClient(client_model *client)
{
    ClientTreeItem *item = new ClientTreeItem(client);
    clientTree.insert(client->unit_ID, item);
    units_item.addChild(item);
}

void QuestTreeWidget::AddQuest(Quest *quest)
{
    if (!typeItemMap.contains(quest->questType))
    {
        QTreeWidgetItem *root = new QTreeWidgetItem();
        root->setData(0,0,QVariant(Quest::QuesTypeString(quest->questType)));
        addTopLevelItem(root);
        typeItemMap.insert(quest->questType, root);
        root->setExpanded(true);
    }
    QuestTreeItem *item = new QuestTreeItem(quest);
    typeItemMap[quest->questType]->addChild(item);
    questItemMap.insert(quest, item);

    questItems.insert(quest->id, item);

    item->setExpanded(true);

    qDebug() << "item added";
}

Quest* QuestTreeWidget::AddQuest(Quest::QuestType type, int selectModelId)
{
    Quest *quest = new Quest();
    quest->questType = type;
    quest->selectedModelId = selectModelId;
    AddQuest(quest);
    return quest;
}

void QuestTreeWidget::RemoveQuestById(int id)
{
    QList<Quest*> quests = questItemMap.keys();
    foreach(Quest *quest, quests)
    {
        if (quest->id == id)
        {
            QTreeWidgetItem *item = questItemMap[quest];
            questItemMap.remove(quest);            
            typeItemMap[quest->questType]->removeChild(item);

            for(int i =0; i < item->childCount(); i++)
            {
                QTreeWidgetItem *temp = item->child(i);
                item->removeChild(temp);
                units_item.addChild(temp);
            }

            break;
        }
    }
    questItems.remove(id);
}

void QuestTreeWidget::QuestUpdate(Quest *quest)
{
    if (questItemMap.contains(quest))
    {
        QTreeWidgetItem *item = questItemMap[quest];
        item->setData(0, 0, QVariant(QString("quest %1").arg(quest->id)));
        item->setData(1, 0, QVariant(Quest::QuestStateString()[quest->questState]));
        item->setData(2, 0, QVariant("Unit"));
        item->setData(3, 0, QVariant(quest->createTime));
        item->setData(4, 0, QVariant(quest->endTime));
        qDebug() << "item updated";
    }
}

void QuestTreeWidget::QuestChangeState(Quest *quest, Quest::QuestState state)
{
    if (questItemMap.contains(quest))
    {
        QTreeWidgetItem *item = questItemMap[quest];
        item->setData(1, 0, QVariant(Quest::QuestStateString()[state]));
        qDebug() << "item state updated";
    }
}

void QuestTreeWidget::MoveClientToQuest(int clientId, int QuestId)
{
    ClientTreeItem *clientItem;
    QuestTreeItem *questItem;
    if (clientTree.keys().contains(clientId))
        clientItem = clientTree[clientId];
    else return;
    if (questItems.keys().contains(QuestId))
        questItem = questItems[QuestId];
    else return;

//    units_item.removeChild(clientItem);
    clientItem->parent()->removeChild(clientItem);
    questItem->addChild(clientItem);

    update();
}
