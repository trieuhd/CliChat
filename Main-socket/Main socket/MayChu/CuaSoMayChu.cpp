#include "CuaSoMayChu.h"

CuaSoMayChu::CuaSoMayChu () {
   
    trangThai = new QLabel();
    thoat = new QPushButton(tr("Thoát"));
    connect(thoat, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *lop = new QVBoxLayout();
    lop->addWidget(trangThai);
    lop->addWidget(thoat);
    setLayout(lop);

    setWindowTitle(tr("Máy chủ"));

    mayChu = new QTcpServer(this);
    if (!mayChu->listen(QHostAddress::Any, 50885)) {
        // Neu may chu chua duoc khoi dong
        trangThai->setText(tr("Máy chủ chưa khởi động được. Lý do :<br />") +mayChu->errorString());
    } else {
        // Neu may chu duoc khoi dong thanh cong
        trangThai->setText(tr("Máy chủ được mở trên cổng <strong>") + QString::number(mayChu->serverPort()) + tr("</strong>.<br />Người dùng có thể nhanh chóng kết nối để tán gẫu."));
        connect(mayChu, SIGNAL(newConnection()), this, SLOT(ketNoiMoi()));
    }

    kichThuoc = 0;
}

void CuaSoMayChu::ketNoiMoi() {
    guiTinNhanChoMoiNguoi (tr("<em>Một người mới  vừa tham gia với chúng ta !</em>"));

    QTcpSocket *nguoiDungMoi = mayChu->nextPendingConnection();
    nguoiDung << nguoiDungMoi;

    connect(nguoiDungMoi, SIGNAL(readyRead()), this, SLOT(nhanDuLieu()));
    connect(nguoiDungMoi, SIGNAL(disconnected()), this, SLOT(ngatKetNoi()));
}

void CuaSoMayChu::nhanDuLieu() {
QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) { 
        return;
    }
    QDataStream in(socket);
    if (kichThuoc == 0) { //Neu chua biet kich thuoc tin nhan thi chung ta se thu tim trong goi du lieu vua toi
         if (socket->bytesAvailable() < (int)sizeof(quint16)) { 
             return;
        }
        in >> kichThuoc; 
    }
    // Biet kich thuoc, chung ta se kiem tra xem da nhan duoc toan bo tin nhan chua
    if (socket->bytesAvailable() < kichThuoc) { 
        return;
    }
    QString tinNhan;
    in >> tinNhan;

    guiTinNhanChoMoiNguoi(tinNhan);

    // Dat lai kich thuoc la 0 de cho tin nhan tiep theo
    kichThuoc = 0;

}

void CuaSoMayChu::ngatKetNoi() {
    guiTinNhanChoMoiNguoi(tr("<em>1 người dùng vừa mới rời đi</em>"));

    // Xac dinh xem ai la nguoi ngat ket noi
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Neu khong tim thay nguoi gui tin hieu thi huy bo xu ly
        return;

    nguoiDung.removeOne(socket);

    socket->deleteLater();
}
void CuaSoMayChu::guiTinNhanChoMoiNguoi(const QString &tinNhan) {
    // Chuan bi tin nhan gui di
    QByteArray goiTinNhan;
    QDataStream out(&goiTinNhan, QIODevice::WriteOnly);

    out << (quint16) 0; // Viet gia tri 0 o dau goi tin de dat truoc cho de viet kich thuoc tin nhan
    out << tinNhan; // Viet noi dung tin nhan vao goi tin
    out.device()->seek(0); // Quay ve dau goi tin
    out << (quint16) (goiTinNhan.size() - sizeof(quint16)); 

    for (int i = 0; i < nguoiDung.size(); i++) {
        nguoiDung[i]->write(goiTinNhan);
    }

}

