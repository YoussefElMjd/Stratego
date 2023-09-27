TEMPLATE = app
CONFIG += console c++17
CONFIG += c++17
CONFIG -= app_bundle
#CONFIG -= qt
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors -Wall

SOURCES += \
        controller/controller.cpp \
        controller/controllerGui.cpp \
        main.cpp \
        model/board.cpp \
        model/game.cpp \
        model/gameElement.cpp \
        model/position.cpp \
        observer/observable.cpp \
        view/view.cpp \
        view/viewgui.cpp

HEADERS += \
    controller/controllerGui.h \
    keyboardAndStringConvert/keyboard.hpp \
    keyboardAndStringConvert/keyboard.hpp \
    keyboardAndStringConvert/stringConvert.hpp \
    keyboardAndStringConvert/stringConvert.hpp \
    controller/controller.h \
    model/board.h \
    model/controller.h \
    model/enum.h \
    model/game.h \
    model/gameElement.h \
    model/position.h \
    model/view.h \
    observer/observable.h \
    observer/observer.h \
    view/view.h \
    view/viewgui.h

DISTFILES += \
    ../../Desktop/ressources/communityIcon_i69s9qgzn1541.png \
    ../../Desktop/ressources/stratego.png \
    battleField.txt \
    ressources/water.jpg

FORMS += \
    viewgui.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc
