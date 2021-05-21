#ifndef QUEST_H
#define QUEST_H

#include <QDateTime>

class Quest
{

    enum QestType{ None, Visit, Clear, Overflow};
    /*
     * None - нет задачи
     * Visit - осмотр
     * Clear - уборка
     * Overflow - переполнение (необходимо убрать место хранения)
     */

public:
    Quest();

    int hostId; // Кто дал задачу
    QDateTime createTime; // Время постановки задачи
    QDateTime endTime; // Время выполнения задачи

    QestType questType;
    QString test; // Текст задачи (подробности)

    // TODO добавить область выполнения задачи
};

#endif // QUEST_H
