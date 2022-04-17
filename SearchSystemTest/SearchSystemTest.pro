include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += "../SearchSystem/Include"

SOURCES += \
        ../SearchSystem/Source/Algorithms.cpp \
        ../SearchSystem/Source/SearchSystemContainer.cpp \
        AlgorithmsTests.cpp \
        SearchSystemContainerTest.cpp \
        main.cpp        

HEADERS += \
    ../SearchSystem/Include/Algorithms.h \
    ../SearchSystem/Include/SearchSystemContainer.h

LIBS += -ltbb
