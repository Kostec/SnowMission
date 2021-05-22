QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/questcontroller.cpp \
    CustomWidgets/TreeItems/clienttreeitem.cpp \
    CustomWidgets/TreeItems/questtreeitem.cpp \
    CustomWidgets/mapview.cpp \
    CustomWidgets/questtreewidget.cpp \
    CustomWidgets/scene_view.cpp \
    Model/quest.cpp \
    Models/client_model.cpp \
    Models/graphics_model.cpp \
    Models/select_model.cpp \
    main.cpp \
    mainwindow.cpp \
    server/packets/abstract_packet_class.cpp \
    server/packets/inform_packet1.cpp \
    server/packets/type_packet.cpp \
    server/server.cpp

HEADERS += \
    Controllers/questcontroller.h \
    CustomWidgets/TreeItems/clienttreeitem.h \
    CustomWidgets/TreeItems/questtreeitem.h \
    CustomWidgets/mapview.h \
    CustomWidgets/questtreewidget.h \
    CustomWidgets/scene_view.h \
    Model/quest.h \
    Models/client_model.h \
    Models/graphics_model.h \
    Models/select_model.h \
    mainwindow.h \
    server/packets/abstract_packet_class.h \
    server/packets/inform_packet1.h \
    server/packets/type_packet.h \
    server/server.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
