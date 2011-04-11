QT          += core gui
TARGET       = Taggressive
TEMPLATE     = app
INCLUDEPATH += /usr/include/taglib
LIBS        += /usr/lib/libtag.so
SOURCES     += main.cpp \
               taggressive.cpp
HEADERS     += taggressive.h
FORMS       += taggressive.ui
