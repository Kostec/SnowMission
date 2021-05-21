#include "quest.h"

Quest::Quest()
{
    createTime = QDateTime::currentDateTime();
    questState = Quest::QuestState::New;
}

