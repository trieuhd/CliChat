#include "CuaSoMayChu.h"
#include<QDate>
#include<QTime>
#include<QFile>;
#include<QTextStream>
#include<QTcpSocket>
QDate cd= QDate::currentDate();
QTime ct=QTime::currentTime();
void CuaSoMayChu::ghiFile(QString tinnhan,QString filename){
    QTextStream out(stdout);
    QFile file(filename);
    if(file.open(QIODevice::Append|QIODevice::WriteOnly)){
        QTextStream out(&file);

        out<<tinnhan<<endl;

    }
}

QString CuaSoMayChu::docFileTheoSoDong( QString tenfile, int a){
    QTextStream out(stdout);
    QFile file(tenfile);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    QString line1, line;
    int i=0;
    QTextStream in(&file);
    while (!in.atEnd()) {
        line= in.readLine();
        i++;

    }
    file.close();

    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long CHon Lai File!!");
    }

    int b=0;
    while (!in.atEnd()) {
        line= in.readLine();
        b++;
       if(b>=i-a)
           line1=line1+"<br>"+line;
    }
    file.close();
    return line1;

}
QString CuaSoMayChu::docFile(QString filename){
    QTextStream out(stdout);
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    QString line1, line;
    int i=0;
    QTextStream in(&file);
    line=in.readLine();
    file.close();
    return line;

}


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

        trangThai->setText(tr("Máy chủ chưa khởi động được. Lý do :<br />") +mayChu->errorString());
    } else {

        trangThai->setText(tr("Máy chủ được mở trên cổng <strong>") + QString::number(mayChu->serverPort()) +tr(" Vào Lúc ")+ ct.toString() + tr("</strong>.<br />Người dùng có thể nhanh chóng kết nối để tán gẫu."));
        connect(mayChu, SIGNAL(newConnection()), this, SLOT(ketNoiMoi()));
    }

    kichThuoc = 0;
}






void CuaSoMayChu::nhanDuLieu() {
//   QString filename1="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listmessage.txt";
QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) { 
        return;
    }
    QDataStream in(socket);
    if (kichThuoc == 0) {
         if (socket->bytesAvailable() < (int)sizeof(quint16)) { 
             return;
        }
        in >> kichThuoc; 
    }

    if (socket->bytesAvailable() < kichThuoc) { 
        return;
    }
    QString filemessage="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listmessage.txt";
    QString tinnhan;
    in >> tinnhan;
    QString length = cd.toString()+ " " +tinnhan;

    ghiFile(length,filemessage);
//    QString lenh= tinnhan.mid(38,tinnhan.count());
//    QFile file3(filename3);
//    if(!file3.open(QIODevice::ReadOnly)){
//        qWarning("Ko the mo file");
//    }
//    if(lenh=="/info"){
//        QTextStream out(stdout);

//        QTextStream in(&file3);

//        while (!in.atEnd()) {
//            QString line= in.readAll();

//            guiTinNhanChoMoiNguoi(line);
//        }
//        file3.close();


//    }
//    else {
        guiTinNhanChoMoiNguoi(tinnhan);




    kichThuoc = 0;

}

void CuaSoMayChu::ngatKetNoi() {
    guiTinNhanChoMoiNguoi(tr("<em>1 người dùng vừa mới rời đi</em>"));
    QString filename="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/tinhieukethuc.txt";
    QString a=docFile(filename);
    if(a.size()!=0){
        guiTinNhanChoMoiNguoi("<em>Chu Phong Da Ra Khoi Phong, Phong Dong lai ...</em>");
        thoat->click();
    }

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0)
        return;

    nguoiDung.removeOne(socket);

    socket->deleteLater();
}
void CuaSoMayChu::guiTinNhanChoMoiNguoi(const QString &tinNhan) {

    QByteArray goiTinNhan;
    QDataStream out(&goiTinNhan, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << tinNhan;
    out.device()->seek(0);
    out << (quint16) (goiTinNhan.size() - sizeof(quint16)); 

    for (int i = 0; i < nguoiDung.size(); i++) {
        nguoiDung[i]->write(goiTinNhan);
    }

}
void CuaSoMayChu::guiTinNhanChoMotNguoi(const QString &tinNhan, int i) {

    QByteArray goiTinNhan;
    QDataStream out(&goiTinNhan, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << tinNhan;
    out.device()->seek(0);
    out << (quint16) (goiTinNhan.size() - sizeof(quint16));

        nguoiDung[i]->write(goiTinNhan);


}
void CuaSoMayChu::ketNoiMoi() {
    QString listusermoi="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt";
     QString listuser="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listuser.txt";
    QString listmessage="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listmessage.txt";
    QString info="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/info.txt";
    guiTinNhanChoMoiNguoi (tr("<em>Một người mới  vừa tham gia với chúng ta !</em>"));

    QTcpSocket *nguoiDungMoi = mayChu->nextPendingConnection();
    nguoiDung << nguoiDungMoi;
    connect(nguoiDungMoi, SIGNAL(readyRead()), this, SLOT(nhanDuLieu()));
    connect(nguoiDungMoi, SIGNAL(disconnected()), this, SLOT(ngatKetNoi()));
    if(nguoiDung.size()==1){
             QString new1=docFileTheoSoDong(listmessage,4);
             QString new2=docFileTheoSoDong(listuser,6);

            guiTinNhanChoMoiNguoi(tr("<em>Bạn Đã Là Chủ Phòng Chát!! Thế Giới Này Bây Giờ Là Của Bạn<br>5 Cuoc Tro Chuyen Gan Nhat la:<br></em>")+new1+"<br>Cac Thanh Vien Lan Truoc La:<br>"+new2);
//            guiTinNhanChoMoiNguoi(tr("<em>5 Cuoc Tro Chuyen Gan Nhat la</em>"));

            guiTinNhanChoMoiNguoi(new1);


        QString temp1="Phong Duoc Tao Vao Luc " +ct.toString()+ " " + cd.toString()+"<br>";
        QString temp2="Nguoi Tao Phong La: "+ docFile(listusermoi) ;
        QString temp3="Noi Quy Phong: <br> Cam Noi Tuc Chui Bay<br>Cam Gay War<br>Cam Hop Ban Chinh Tri";
        ghiFile(temp1,info);
        ghiFile(temp2,info);
        ghiFile(temp3,info);
    }
    if(nguoiDung.size()>1){
    for (int i=0;i<nguoiDung.size();i++) {

            guiTinNhanChoMotNguoi("<em>Chao Mung Ban Den Voi Phong Chat, Tung Hoa, Tung Hoa!!</em>",i);

        }
    }





//    if(nguoiDung.size()==1){
//        guiTinNhanChoMotNguoi(ct.toString()+tr("<em> Bạn Đã Là Chủ Phòng Chát!! Thế Giới Này Bây Giờ Là Của Bạn</em>"),0);
//        QString temp="Phong Duoc Tao Vao Luc "+ ct.toString();
//        QString temp2="CHU Phong La: hung123 ";
//        QString temp3="Quy Dinh: KO NOI TUC CHUI BAY GAY WAR";
//        QString filename2="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/info.txt";
//        QTextStream out(stdout);
//        QFile file2(filename2);
//        if(file2.open(QIODevice::WriteOnly)){
//            QTextStream out(&file2);

//            for(int i=0;i<nguoiDung.size();i++){
//                   out<<temp<<endl;
//                    out<<temp2<<endl;
//                     out<<temp3<<endl;


//            }
//    }

//    }
//    for (int b=0;b<=nguoiDung.size();b++) {

//        if(nguoiDung.size()!= 1&& b == nguoiDung.size()-1){
//        guiTinNhanChoMotNguoi("<em>Chào Mừng Bạn Đến Với Phòng Chát! Tung Hoa , Tung Hoa!!</em>", b == nguoiDung.size()-1);
//    }
//    }

//        QString filename="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listSocKet.txt";
//        QTextStream out(stdout);

//        QFile file1(filename);
//        if(file1.open(QIODevice::WriteOnly)){
//            QTextStream out(&file1);

//            for(int i=0;i<nguoiDung.size();i++){
//                   out<<nguoiDung[i]<<endl;



//    }}
}



