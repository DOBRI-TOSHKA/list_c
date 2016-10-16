TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    ./lib_src/my_list_two_forked.c

HEADERS += \
    ./lib_src/my_list_two_forked.h
