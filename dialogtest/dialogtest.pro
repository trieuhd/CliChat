

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dialogtest
TEMPLATE = app


QT += \
    widgets \
    network
SOURCES += \
       main.cpp \
    CuaSoNguoiDung.cpp \
    Menu.cpp \
    CuaSoNguoiDungKhach.cpp

HEADERS += \
    Menu.h \
    CuaSoNguoiDungKhach.h \
    CuaSoNguoiDungChu.h

FORMS += \
    CuaSoNguoiDungKhach.ui \
    CuaSoNguoiDungChu.ui
