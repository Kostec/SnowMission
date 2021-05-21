#include "questtreewidget.h"
#include <QDebug>

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
}

void QuestTreeWidget::dropEvent(QDropEvent *event)
{
    qDebug() << "drop event";
}

void QuestTreeWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "drag leave event";
}

void QuestTreeWidget::AddQuest(Quest *quest)
{
    if (typeItemMap.contains(quest->questType))
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setData(0, 0, QVariant(QString("quest %1").arg(quest->id)));
        item->setData(1, 0, QVariant(Quest::QuestStateString()[quest->questState]));
        item->setData(2, 0, QVariant("Unit"));
        item->setData(3, 0, QVariant(quest->createTime));
        item->setData(4, 0, QVariant(quest->endTime));
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
        item->setData(1, 0, QVariant(Quest::QuestStateString()[quest->questState]));
        qDebug() << "item state updated";
    }
}
