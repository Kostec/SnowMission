#ifndef QUEST_H
#define QUEST_H

#include <QObject>

#include <QDateTime>
#include <QMap>

class Quest: QObject
{
    Q_OBJECT
public:
    enum QuestType{ None = 0, Visit, Clear, Overflow};
    /*
     * None - нет задачи
     * Visit - осмотр
     * Clear - уборка
     * Overflow - переполнение (необходимо убрать место хранения)
     */
    enum QuestState { New = 0, Processing, Checking, Complete };

    static const QMap<Quest::QuestState, QString> QuestStateString(){
        QMap<Quest::QuestState, QString> map;
        map.insert(Quest::QuestState::New, "New");
        map.insert(Quest::QuestState::Processing, "Processing");
        map.insert(Quest::QuestState::Checking, "Checking");
        map.insert(Quest::QuestState::Complete, "Complete");
        return map;
    };

public:
    Quest();

    int id; // Идентификатор задания
    int hostId; // Кто дал задачу
    QDateTime createTime; // Время постановки задачи
    QDateTime endTime; // Время выполнения задачи
    QString test; // Текст задачи (подробности)
    // TODO добавить область выполнения задачи

//    QuestType getQuestType() const;
//    void setQuestType(const QuestType &value);

//    QuestState getQuestState() const;
//    void setQuestState(const QuestState &value);

//private:
    QuestType questType;
    QuestState questState;

};

#endif // QUEST_H
