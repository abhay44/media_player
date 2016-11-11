
TARGET      = simple-player
TEMPLATE    = app
CONFIG 	   += c++11

QT         += widgets

SOURCES    += main.cpp \
    SimplePlayer.cpp

HEADERS    += SimplePlayer.h

FORMS      += SimplePlayer.ui
LIBS       += -lVLCQtCore -lVLCQtWidgets



RESOURCES += \
    icons.qrc
