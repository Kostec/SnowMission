#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->layout()->addWidget(&questWidget);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

