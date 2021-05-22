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

    Scene_view *map = new Scene_view();
    map->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

