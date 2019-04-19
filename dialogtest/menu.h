#ifndef MENU_H
#define MENU_H
#include<QDialog>
#include<QtWidgets>


class Menu:public QWidget
{
    Q_OBJECT

public:
    Menu();
private slots:
    void AnTao();
    void AnVao();
private:
    QPushButton *taoPhong;
    QPushButton *vaoPhong;
    QPushButton *exit;

};

#endif
