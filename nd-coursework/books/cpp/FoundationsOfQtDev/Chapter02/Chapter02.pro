# Listing 2-1: Phone book application's project file
TEMPLATE = app
TARGET   = addressbook

SOURCES += main.cpp editdialog.cpp listdialog.cpp
HEADERS += editdialog.h listdialog.h
FORMS   += editdialog.ui listdialog.ui

QT += widgets

CONFIG += sdk_no_version_check

QMAKE_MACOSX_DEPLOYMENT_TARGET = 11.0
