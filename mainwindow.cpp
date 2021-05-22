#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->centralWidget()->setLayout(&mainLayout);

    Quest *quest = new Quest();
    quest->id = 123;
    quest->questType = Quest::QuestType::Visit;
    questWidget.AddQuest(quest);

    quest = new Quest();
    quest->id = 1;
    quest->questType = Quest::QuestType::Visit;
    questWidget.AddQuest(quest);
    quest = new Quest();
    quest->id = 2;
    quest->questType = Quest::QuestType::Clear;
    questWidget.AddQuest(quest);
    quest = new Quest();
    quest->id = 3;
    quest->questType = Quest::QuestType::Clear;
    questWidget.AddQuest(quest);

    mainLayout.addWidget(&questWidget);

    mainLayout.addWidget(&view);

    client_model *client = new client_model(nullptr);
    client->Lalittude = 12.5;
    client->Longituge = 45.5;
    client->Power = 100;
    client->Status = 87;
    client->Velosity = 5.5;
    client->Work_id = 99;
    questWidget.AddClient(client);

    connect(&server, SIGNAL(new_client(client_model*)), &questWidget, SLOT(AddClient(client_model*)));
    Scene_view *map = new Scene_view();
    map->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

