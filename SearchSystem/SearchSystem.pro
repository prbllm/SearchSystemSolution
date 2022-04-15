TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wno-misleading-indentation

INCLUDEPATH += Include

SOURCES += \
    Source/Algorithms.cpp \
    Source/SearchSystem.cpp \
    Source/SearchSystemContainer.cpp

HEADERS += \
    Include/Algorithms.h \
    Include/Def.h \
    Include/Document.h \
    Include/SearchSystemContainer.h

LIBS += -ltbb
