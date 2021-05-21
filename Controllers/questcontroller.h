#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include <QObject>

#include <Model/quest.h>

class QuestController: QObject
{
    Q_OBJECT
public:
    QuestController();

    QList<Quest> quests;

    void AddQuest(Quest *quest);
    void QuestComplete(Quest *quest);

//signals:
//    void QuestCompleted(Quest *quest);
};


#endif // QUESTCONTROLLER_H
