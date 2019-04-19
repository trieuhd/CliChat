#ifndef CUASOMAYCHU_H
#define CUASOMAYCHU_H

#include <QtWidgets>
#include <QtNetwork>

class CuaSoMayChu : public QWidget {
    Q_OBJECT

    public:
        CuaSoMayChu();
        void guiTinNhanChoMoiNguoi(const QString &tinNhan);
        void guiTinNhanChoMotNguoi(const QString &tinNhan, int i);
        QString docFileTheoSoDong( QString tenfile, int a);


    private slots:
        void ketNoiMoi();
        void nhanDuLieu();
        void ngatKetNoi();
        void ghiFile(QString tinnhan, QString filename);
        void ghiFile1(QTcpSocket tinnhan);
        void ghiFile2(QTcpSocket tinnhan, QString filename);
        QString docFile( QString filename);

    private:
        QLabel *trangThai;
        QPushButton *thoat;

        QTcpServer *mayChu;
        QList<QTcpSocket *> nguoiDung;
        quint16 kichThuoc;
};

#endif
