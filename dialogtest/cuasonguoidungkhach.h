#ifndef CUASONGUOIDUNGKHACH_H
#define CUASONGUOIDUNGKHACH_H

#include <QtWidgets>
#include <QtNetwork>
#include "ui_CuaSoNguoiDungKhach.h"

class CuaSoNguoiDungKhach : public QDialog, private Ui::CuaSoNguoiDungKhach {
    Q_OBJECT

    public:
        CuaSoNguoiDungKhach();


    private slots:
        void anNutKetNoi();
        void anNutGuiTin();
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


       void moHopThoai2();



    private:
        QTcpSocket *socket; // May chu
        quint16 kichThuoc;
};

#endif
