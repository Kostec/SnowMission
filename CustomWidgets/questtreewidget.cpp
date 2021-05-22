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
    headerList.append("Состояние");
    headerList.append("Исполнитель");
    headerList.append("Дата создание");
    headerList.append("Дата завершения");
    setHeaderLabels(headerList);

    clearNode = new QTreeWidgetItem();
    clearNode->setData(0, 0, QVariant("Clearing"));
    typeItemMap.insert(Quest::QuestType::Clear, clearNode);

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setData(0, 0, QVariant("Visit"));
    typeItemMap.insert(Quest::QuestType::Visit, item);

    addTopLevelItem(clearNode);
    addTopLevelItem(item);

    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);


    clientsNode = new QTreeWidgetItem();
    clientsNode->setData(0, 0, QVariant("Units"));
    addTopLevelItem(clientsNode);
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
            mimeData->setProperty("client_id", QVariant(static_cast<ClientTreeItem*>(treeItem)->client->Work_id));
            drag->setMimeData(mimeData);

            event->accept();

            Qt::DropAction result = drag->exec( Qt::MoveAction );
            qDebug() << "Drop action result: " << result;
        }
    }
}


void QuestTreeWidget::AddClient(client_model *client)
{
    QTreeWidgetItem *item = new ClientTreeItem(client);
    clientsNode->addChild(item);
}


void QuestTreeWidget::AddQuest(Quest *quest)
{
    if (typeItemMap.contains(quest->questType))
    {
        QTreeWidgetItem *item = new QuestTreeItem(quest);
        typeItemMap[quest->questType]->addChild(item);
        questItemMap.insert(quest, item);
        qDebug() << "item added";
    }
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
