#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T07:35:19
#
#-------------------------------------------------

QT       += core gui

CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Theo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    exif.cpp \
    helpdialog.cpp \
        main.cpp \
        theo.cpp \
    mygraphicsscene.cpp \
    mygraphicsview.cpp

HEADERS += \
    exif.h \
    helpdialog.h \
        theo.h \
    mygraphicsscene.h \
    nr3.h \
    mygraphicsview.h

FORMS += \
        helpdialog.ui \
        theo.ui

#LIBS += \
#    libc-2.27.so \
#    libgcc_s.so.1 \
#    libm-2.27.so \
#    libQt5Core.so.5.9.5 \
#    libQt5Gui.so.5.9.5 \
#    libQt5Widgets.so.5.9.5 \
#    libstdc++.so.6.0.25

