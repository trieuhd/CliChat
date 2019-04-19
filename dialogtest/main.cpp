#include "CuaSoNguoiDungChu.h"
#include "CuaSoNguoiDungKhach.h"
#include"Menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu demo;
    demo.show();
    return a.exec();


}

