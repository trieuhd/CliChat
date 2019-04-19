#include "Menu.h"
#include"CuaSoNguoiDungKhach.h"
#include"CuaSoNguoiDungChu.h"
#include<QApplication>

Menu::Menu()
{
    taoPhong=new QPushButton("CREAT ROOM");
    vaoPhong=new QPushButton("JOIN ROOM");
    exit=new QPushButton("EXIT");
    QVBoxLayout *lop=new QVBoxLayout();
    lop->addWidget(taoPhong);
    lop->addWidget(vaoPhong);
    lop->addWidget(exit);
    setLayout(lop);
    resize(450,350);
    setWindowTitle("HELLO!");

    connect(taoPhong,SIGNAL(clicked()),this,SLOT(AnTao()));
    connect(vaoPhong,SIGNAL(clicked()),this,SLOT(AnVao()));
    connect(exit,SIGNAL(clicked()),qApp,SLOT(quit()));
}
void Menu::AnTao(){
CuaSoNguoiDungChu *cuaso=new CuaSoNguoiDungChu();
    cuaso->exec();
}
void Menu::AnVao(){
    CuaSoNguoiDungKhach *cuasokhach= new CuaSoNguoiDungKhach();
    cuasokhach->exec();
}

