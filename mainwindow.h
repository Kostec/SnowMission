#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <CustomWidgets/questtreewidget.h>
#include "CustomWidgets/scene_view.h"

#include <server/server.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHBoxLayout mainLayout;

    QuestTreeWidget questWidget;

    Scene_view *map;

    QGraphicsScene scene;

//    Server server;

public slots:
    void CreateQuest(Quest::QuestType type, int selectModelid);
    void RemoveQuest(int questId);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
