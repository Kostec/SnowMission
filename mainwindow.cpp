#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<QList<QPoint>>("List of points");
    this->centralWidget()->setLayout(&mainLayout);
    questWidget.setMinimumWidth(250);

    map = new Scene_view();

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(&questWidget);
    splitter->addWidget(map);
    mainLayout.addWidget(splitter);

    map->show();
    connect(&server, SIGNAL(new_client(client_model*)), map, SLOT(new_unit(client_model*)));
    server.spawn(30);

//    connect(&server, SIGNAL(new_client(client_model*)), map, SLOT(new_unit(client_model*)));

//    server.spawn(5);

    connect(map, SIGNAL(createQuest(Quest::QuestType, int)), this, SLOT(CreateQuest(Quest::QuestType, int)));

    connect(map, SIGNAL(removeQuest(int)), this, SLOT(RemoveQuest(int)));

    connect(map,SIGNAL(addClientToTree(client_model* )),this,SLOT(AddClientToTree(client_model *)));

    foreach(client_model* client, map->client_list)
        questWidget.AddClient(client);

    questWidget.selectModels = &map->selectModels;
    questWidget.client_list = &map->client_list;

    connect(map, SIGNAL(moveClientToSelect(int, int)), this, SLOT(MoveClientToSelect(int, int)));
}

void MainWindow::MoveClientToSelect(int clientId, int questId)
{
    questWidget.MoveClientToQuest(clientId, questId);
}

void MainWindow::CreateQuest(Quest::QuestType type, int selectModelid)
{
    Quest *quest = questWidget.AddQuest(type, selectModelid);
    foreach(Select_model *model, map->selectModels)
    {
        if (model->id == quest->selectedModelId)
        {
            model->questId = quest->id;
        }
    }
}

void MainWindow::RemoveQuest(int questId)
{
    questWidget.RemoveQuestById(questId);

}
void MainWindow::AddClientToTree(client_model* client)
{
    questWidget.AddClient(client);
}

MainWindow::~MainWindow()
{
    delete ui;
}

