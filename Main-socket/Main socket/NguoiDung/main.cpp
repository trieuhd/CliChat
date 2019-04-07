#include <QApplication>
#include "CuaSoNguoiDung.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CuaSoNguoiDung cuaSo;
    cuaSo.show();

    return app.exec();
}

