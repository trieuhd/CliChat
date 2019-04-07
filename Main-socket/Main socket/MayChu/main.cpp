#include <QApplication>
#include "CuaSoMayChu.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CuaSoMayChu cuaSo;
    cuaSo.show();

    return app.exec();
}

