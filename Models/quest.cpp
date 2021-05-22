#include "quest.h"

Quest::Quest()
{
    id = idCount++;
    createTime = QDateTime::currentDateTime();
    questState = Quest::QuestState::New;
}

