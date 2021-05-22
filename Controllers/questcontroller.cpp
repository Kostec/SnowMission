#include "questcontroller.h"

QuestController::QuestController()
{

}

void QuestController::new_client(client_model *client)
{
    clients.append(client);
}
