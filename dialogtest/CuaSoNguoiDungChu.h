#ifndef CUASONGUOIDUNGCHU_H
#define CUASONGUOIDUNGCHU_H

#include <QtWidgets>
#include <QtNetwork>
#include "ui_CuaSoNguoiDungChu.h"

class CuaSoNguoiDungChu : public QDialog, private Ui::CuaSoNguoiDungChu {
    Q_OBJECT

    public:
        CuaSoNguoiDungChu();
        void GhiViTri(QString a);

    private slots:
        void anNutKetNoi();
        void anNutGuiTin();
        void tinHieuKetThuc();
        void anEnterGuiTin();
        void nhanDuLieu();
        void ketNoi();
        void ngatKetNoi();
        void loiSocket(QAbstractSocket::SocketError loi);
        void anEnter();
        QString docFileTheoSoDong( QString tenfile, int sodonglayra);
        QString docFileTatCa( QString tenfile);
        QString timNguoiOffline(QString tenfile1,QString tenfile2);
        int XacDinhMod(QString tinnhan);


       void ghiFileTatCa(QString tinnhan,QString filename);
       void ghiFileMoi(QString tinnhan,QString filename);
       void moHopThoai();
       void moHopThoai1();
       void moHopThoai2();
       void moHopThoai3();
       void moHopThoai4();


    private:
        QTcpSocket *socket; // May chu
        quint16 kichThuoc;
};

#endif
