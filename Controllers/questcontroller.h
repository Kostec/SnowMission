#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include <QObject>

#include <Models/quest.h>

#include <Models/client_model.h>

class QuestController: QObject
{
    Q_OBJECT
public:
    QuestController();

    QList<Quest*> quests;
    QList<client_model*> clients;

    void AddQuest(Quest *quest);
    void QuestComplete(Quest *quest);

//signals:
//    void QuestCompleted(Quest *quest);
public slots:
    void new_client(client_model *client);
};


#endif // QUESTCONTROLLER_H
