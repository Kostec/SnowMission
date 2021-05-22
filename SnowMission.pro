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
    CustomWidgets/TreeItems/treeitem.cpp \
    CustomWidgets/questtreewidget.cpp \
    CustomWidgets/scene_view.cpp \
    Models/client_model.cpp \
    Models/graphics_model.cpp \
    Models/quest.cpp \
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
    CustomWidgets/TreeItems/treeitem.h \
    CustomWidgets/questtreewidget.h \
    CustomWidgets/scene_view.h \
    Models/client_model.h \
    Models/graphics_model.h \
    Models/quest.h \
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

DISTFILES += \
    stylesheets/Hmovetoolbar_dark.svg \
    stylesheets/Hmovetoolbar_light.svg \
    stylesheets/Hsepartoolbar_dark.svg \
    stylesheets/Hsepartoolbar_light.svg \
    stylesheets/Vmovetoolbar_light.svg \
    stylesheets/Vsepartoolbar_dark.svg \
    stylesheets/Vsepartoolbar_light.svg \
    stylesheets/background_freecad.svg \
    stylesheets/blender.qss \
    stylesheets/branch_end_closed_dark.svg \
    stylesheets/branch_end_closed_light.svg \
    stylesheets/branch_end_dark.svg \
    stylesheets/branch_end_light.svg \
    stylesheets/branch_end_open_dark.svg \
    stylesheets/branch_end_open_light.svg \
    stylesheets/branch_more_closed_dark.svg \
    stylesheets/branch_more_closed_light.svg \
    stylesheets/branch_more_dark.svg \
    stylesheets/branch_more_light.svg \
    stylesheets/branch_more_open_dark.svg \
    stylesheets/branch_more_open_light.svg \
    stylesheets/branch_vline_dark.svg \
    stylesheets/branch_vline_light.svg \
    stylesheets/checkbox_indeterminate_light.svg \
    stylesheets/checkbox_light.svg \
    stylesheets/close_dark.svg \
    stylesheets/close_light.svg \
    stylesheets/dark-blue.qss \
    stylesheets/dark-green.qss \
    stylesheets/dark-orange.qss \
    stylesheets/down_arrow_dark.svg \
    stylesheets/down_arrow_darker.svg \
    stylesheets/down_arrow_disabled_dark.svg \
    stylesheets/down_arrow_disabled_light.svg \
    stylesheets/down_arrow_light.svg \
    stylesheets/down_arrow_lighter.svg \
    stylesheets/horizontal_line.svg \
    stylesheets/left_arrow_dark.svg \
    stylesheets/left_arrow_darker.svg \
    stylesheets/left_arrow_disabled_dark.svg \
    stylesheets/left_arrow_disabled_light.svg \
    stylesheets/left_arrow_light.svg \
    stylesheets/left_arrow_lighter.svg \
    stylesheets/light-blue.qss \
    stylesheets/light-green.qss \
    stylesheets/light-orange.qss \
    stylesheets/more_dark.svg \
    stylesheets/more_light.svg \
    stylesheets/radiobutton_light.svg \
    stylesheets/right_arrow_dark.svg \
    stylesheets/right_arrow_darker.svg \
    stylesheets/right_arrow_disabled_dark.svg \
    stylesheets/right_arrow_disabled_light.svg \
    stylesheets/right_arrow_light.svg \
    stylesheets/right_arrow_lighter.svg \
    stylesheets/sizegrip_dark.svg \
    stylesheets/sizegrip_light.svg \
    stylesheets/splitter_horizontal_dark.svg \
    stylesheets/splitter_horizontal_light.svg \
    stylesheets/splitter_vertical_dark.svg \
    stylesheets/splitter_vertical_light.svg \
    stylesheets/transparent.svg \
    stylesheets/undock_dark.svg \
    stylesheets/undock_light.svg \
    stylesheets/up-down_arrow_dark.svg \
    stylesheets/up-down_arrow_darker.svg \
    stylesheets/up-down_arrow_disabled_dark.svg \
    stylesheets/up-down_arrow_disabled_light.svg \
    stylesheets/up-down_arrow_light.svg \
    stylesheets/up-down_arrow_lighter.svg \
    stylesheets/up_arrow_dark.svg \
    stylesheets/up_arrow_darker.svg \
    stylesheets/up_arrow_disabled_dark.svg \
    stylesheets/up_arrow_disabled_light.svg \
    stylesheets/up_arrow_light.svg \
    stylesheets/up_arrow_lighter.svg \
    stylesheets/vertical_line.svg
