TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors -Wall
SOURCES += \
        controller/controller.cpp \
        main.cpp \
        model/board.cpp \
        model/game.cpp \
        model/gameElement.cpp \
        model/position.cpp \
#        observer/observable.cpp \      # rnvs : comm : inutile
        view/view.cpp

HEADERS += \
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
    view/view.h •

DISTFILES += \
    battleField.txt \
