#include "CuaSoNguoiDung.h"

CuaSoNguoiDung::CuaSoNguoiDung() {
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(nhanDuLieu()));
    connect(socket, SIGNAL(connected()), this, SLOT(ketNoi()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(ngatKetNoi()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(loiSocket(QAbstractSocket::SocketError)));

    connect(nutKetNoi, SIGNAL(clicked()), this, SLOT(anNutKetNoi()));
    connect(nutGuiTin, SIGNAL(clicked()), this, SLOT(anNutGuiTin()));
    connect(khungSoanThao, SIGNAL(returnPressed()), this, SLOT(anEnterGuiTin()));

    kichThuoc = 0;
}

// Thiet lap ket noi den may chu
void CuaSoNguoiDung::anNutKetNoi() {
    // Thong bao la ket noi dang duoc thuc hien
    cuocHoiThoai->append(tr("<em>Đang kết nối...</em>"));
    nutKetNoi->setEnabled(false);

    socket->abort();
    socket->connectToHost(ipMayChu->text(), congMayChu->value()); // Ket noi toi may chu
}

// Gui tin den may chu
void CuaSoNguoiDung::anNutGuiTin() {
    QByteArray goiTin;
    QDataStream out(&goiTin, QIODevice::WriteOnly);

    // Chuan bi goi tin de gui di
    QString tinGuiDi = tr("<strong>") + nickname->text() +tr("</strong> : ") + khungSoanThao ->text();

    out << (quint16) 0;
    out << tinGuiDi;
    out.device()->seek(0);
    out << (quint16) (goiTin.size() - sizeof(quint16));

    socket->write(goiTin);

    khungSoanThao ->clear(); 
    khungSoanThao ->setFocus();
}

void CuaSoNguoiDung::anEnterGuiTin() {
    anNutGuiTin();
}

void CuaSoNguoiDung::nhanDuLieu() {

    QDataStream in(socket);
    if (kichThuoc == 0) {
         if (socket->bytesAvailable() < (int)sizeof(quint16)) { //Kich thuoc goi tin nho hon kich thuc kieu so nguyen
             return;
        }
        in >> kichThuoc; // Neu nhan duoc kich thuoc tin nhan thi lay ra gia tri do
    }
    // Biet kich thuoc, chung ta se kiem tra xem da nhan duoc toan bo tin nhan chua
    if (socket->bytesAvailable() < kichThuoc) {
        return;
    }
    QString tinNhan;
    in >> tinNhan;

    cuocHoiThoai->append(tinNhan);

    // Dat lai kich thuoc la 0 de cho tin nhan tiep theo
    kichThuoc = 0;

}


void CuaSoNguoiDung::ketNoi() {
    cuocHoiThoai->append(tr("<em>Kết nối thành công !</em>"));
    nutKetNoi->setEnabled(true);
}

void CuaSoNguoiDung::ngatKetNoi() {
    cuocHoiThoai->append(tr("<em>Tạm biệt, hẹn gặp lại sau !</em>"));
}


void CuaSoNguoiDung::loiSocket(QAbstractSocket::SocketError loi) {
    switch(loi) { // Hien thi thong bao khac nhau tuy theo loi gap phai

        case QAbstractSocket::HostNotFoundError:
            cuocHoiThoai->append(tr("<em>LỖI : Không thể kết nối tới máy chủ ! Vui lòng kiểm tra lại địa chỉ IP và cổng truy cập.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            cuocHoiThoai->append(tr("<em>LỖI : Máy chủ từ chối truy cập ! Vui lòng kiểm tra chắc chắn là máy chủ đã được khởi động. Lưu ý đồng thời lỗi địa chỉ IP và cổng truy cập.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            cuocHoiThoai->append(tr("<em>LỖI : Máy chủ đã ngắt kết nối !</em>"));
            break;
        default:
            cuocHoiThoai->append(tr("<em>LỖI : ") + socket->errorString() + tr("</em>"));
    }

    nutKetNoi->setEnabled(true);
}
