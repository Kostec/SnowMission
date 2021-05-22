#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->setLayout(&mainLayout);
    mainLayout.addWidget(&questWidget);

    questWidget.setMinimumWidth(250);
//    connect(&server, SIGNAL(new_client(client_model*)), &questWidget, SLOT(AddClient(client_model*)));

    map = new Scene_view();

    mainLayout.addWidget(map);
    map->show();

//    connect(&server, SIGNAL(new_client(client_model*)), map, SLOT(new_unit(client_model*)));

//    server.spawn(5);

    connect(map, SIGNAL(createQuest(Quest::QuestType, int)), this, SLOT(CreateQuest(Quest::QuestType, int)));

    connect(map, SIGNAL(removeQuest(int)), this, SLOT(RemoveQuest(int)));
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

MainWindow::~MainWindow()
{
    delete ui;
}

