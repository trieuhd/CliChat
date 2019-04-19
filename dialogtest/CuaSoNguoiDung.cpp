#include "CuaSoNguoiDungChu.h"
#include<QDate>
#include<QTime>
#include<QTextStream>
#include<QFile>
#include<QMessageBox>
QDate cd=QDate::currentDate();
QTime ct=QTime::currentTime();


QString CuaSoNguoiDungChu::docFileTheoSoDong( QString tenfile, int a){
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

QString CuaSoNguoiDungChu::docFileTatCa( QString tenfile){
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
       if(b>=i-i)
           line1=line1+"<br>"+line;
    }
    file.close();
    return line1;
}
int CuaSoNguoiDungChu::XacDinhMod( QString a){
    QString listmod="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listban.txt";
    QTextStream out(stdout);

    QFile file(listmod);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    QString line1, line;
    int i=0,b=0;
    QTextStream in(&file);
    while (!in.atEnd()) {
        line= in.readLine();
        i++;
        if(a==line){
        b=i;
        }
    }
    if(b!=0)
        return 1;
    else {
        return 0;
    }

}
void CuaSoNguoiDungChu::ghiFileTatCa(QString tinnhan,QString filename){
    QTextStream out(stdout);
    QFile file(filename);
    if(file.open(QIODevice::Append|QIODevice::WriteOnly)){
        QTextStream out(&file);

        out<<tinnhan<<endl;

    }
}

void CuaSoNguoiDungChu::ghiFileMoi(QString tinnhan,QString filename){

    QTextStream out(stdout);
    QFile file(filename);
     file.deleteLater();

    if(file.open(QIODevice::WriteOnly|QIODevice::Append)){
        QTextStream out(&file);

        out<<tinnhan<<endl;

    }
}
void CuaSoNguoiDungChu::tinHieuKetThuc(){
    QString filename="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/tinhieukethuc.txt";
    QString a="aasdddddddddddddddddddd";
    ghiFileMoi(a,filename);
}
void CuaSoNguoiDungChu::GhiViTri(QString a){
    QTextStream out(stdout);
    QFile file("C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt");
    QString file1="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listbanso.txt";
    QString file3="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listban.txt";
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");
    }
    QString line1, line;
    int i=0,b=0;
    QTextStream in(&file);
    while (!in.atEnd()) {
        line= in.readLine();
        i++;
        if(line==a){
           b=i;
        }

    }
    file.close();
    ghiFileMoi(a,file3);
//    ghiFileTatCa1(b,file1);

}
QString CuaSoNguoiDungChu::timNguoiOffline(QString tenfile1,QString tenfile2){
    QTextStream out(stdout);
    QFile file(tenfile1);
    QFile file2(tenfile2);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    if(!file2.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    QString line1, line;
    int i=0;
    QTextStream in(&file);
    QTextStream in1(&file2);
    for(i=1;i<=25;i++){
        line=in1.readLine();
        while (!in.atEnd()) {
            QString line2=in.readLine();
            if(line==line2)
                i=1;
        }
        if(i!=1)
        line1=line1+"<br>"+line;
    }
    file.close();
    return line1;
}
CuaSoNguoiDungChu::CuaSoNguoiDungChu() {
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(nhanDuLieu()));
    connect(socket, SIGNAL(connected()), this, SLOT(ketNoi()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(ngatKetNoi()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(loiSocket(QAbstractSocket::SocketError)));

    connect(nutKetNoi, SIGNAL(clicked()), this, SLOT(anNutKetNoi()));
    connect(nutGuiTin, SIGNAL(clicked()), this, SLOT(anNutGuiTin()));
    connect(khungSoanThao, SIGNAL(returnPressed()), this, SLOT(anEnterGuiTin()));
    connect(nutThoat,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(nickname,SIGNAL(returnPressed()),this,SLOT(anEnter()));

    kichThuoc = 0;
}
void CuaSoNguoiDungChu::moHopThoai1(){
    int traloi=QMessageBox::question(this,"cauhoi" ,"Ban Chac Chan Roi Phong Chu? Nen Nho Ban Dang La Chu Phong");
    if(traloi==QMessageBox::Yes){



        tinHieuKetThuc();
        nutThoat->click();

    }
}
// Thiet lap ket noi den may chu

void CuaSoNguoiDungChu::moHopThoai(){
   QString content1="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/content.txt";
    bool ok=false;
    QString content=QInputDialog::getText(this,"content","Nhap Noi Dung Conten:",QLineEdit::Normal,QString(), &ok);
    if(ok && !content.isEmpty()){
        ghiFileTatCa(content,content1);
    }else{
        QMessageBox::critical(this,"content","Ban Dang De Trong");
    }

}
void CuaSoNguoiDungChu::moHopThoai2(){
    bool ok=false;
    QString nickname1=QInputDialog::getText(this,"content","Nhap Noi Dung Conten:",QLineEdit::Normal,QString(), &ok);
    if(ok && !nickname1.isEmpty()){
        nickname->setText(nickname1);
    }else{
        QMessageBox::critical(this,"content","Ban Dang De Trong");
    }

}
void CuaSoNguoiDungChu::moHopThoai3(){
    QString listuser="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt";
    QString listuserban="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listuserban.txt";
    bool ok=false;
    QString nickname=QInputDialog::getText(this,"Kick","Nhap User Can Ban:",QLineEdit::Normal,QString(), &ok);
    if(ok && !nickname.isEmpty()){

        GhiViTri(nickname);

    }else{
        QMessageBox::critical(this,"content","Ban Dang De Trong");
    }

}
void CuaSoNguoiDungChu::moHopThoai4(){

        QString listmod="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listmod.txt";

        bool ok=false;
        QString nickname=QInputDialog::getText(this,"addmod","Nhap User Can Them:",QLineEdit::Normal,QString(), &ok);
        if(ok && !nickname.isEmpty()){

           ghiFileTatCa(nickname,listmod);

        }else{
            QMessageBox::critical(this,"That Bai","Ban Dang De Trong");
        }

    }





// Gui tin den may chu
void CuaSoNguoiDungChu::anNutGuiTin() {
     nutKetNoi->setEnabled(false);
    QString info="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/info.txt";
    QString content="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/content.txt";
    QString listmod="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listmod.txt";
    QString listuser="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listuser.txt";
    QString listusermoi="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt";
    QByteArray goiTin;
    QDataStream out(&goiTin, QIODevice::WriteOnly);
    QString content1;
    if(khungSoanThao->text()=="/info"){
        cuocHoiThoai->append(docFileTheoSoDong(info,2));
    }
    else if(khungSoanThao->text()=="/report/all"){
        cuocHoiThoai->append(docFileTatCa(listuser));
    }
    else if(khungSoanThao->text()=="/report/online"){
        cuocHoiThoai->append(docFileTatCa(listusermoi));
    }
    else if(khungSoanThao->text()=="/report/offline"){
        cuocHoiThoai->append(timNguoiOffline(listusermoi,listuser));
    }

    else if(khungSoanThao->text()=="/setinfo"){
        moHopThoai();
    }
    else if(khungSoanThao->text()=="/leave"){
        moHopThoai1();
    }
    else if(khungSoanThao->text()=="/nickname"){
        cuocHoiThoai->append(nickname->text());
    }
    else if(khungSoanThao->text()=="/newnickname"){
        moHopThoai2();
    }
    else if(khungSoanThao->text()=="/newnickname"){
        moHopThoai2();
    }
    else if(khungSoanThao->text()=="/ban"){
        moHopThoai3();
    }
    else if(khungSoanThao->text()=="/mods"){
        cuocHoiThoai->append(docFileTatCa(listmod));
    }
    else if(khungSoanThao->text()=="/addmod"){
        moHopThoai4();
    }
    else if(khungSoanThao->text()=="/d"){
        cuocHoiThoai->append(docFileTatCa(content));

    }
    else if(XacDinhMod(nickname->text())){
         QString tinGuiDi = ct.toString() +  tr(" <strong>") + nickname->text() +tr("</strong> : ") + "<em>"+ khungSoanThao ->text()+"</em>";
    }
    else{

    QString tinGuiDi = ct.toString() +  tr(" <strong>") + nickname->text() +tr("</strong> : ") + khungSoanThao ->text();

    out << (quint16) 0;
    out << tinGuiDi;
    out.device()->seek(0);
    out << (quint16) (goiTin.size() - sizeof(quint16));
    socket->write(goiTin);}
    khungSoanThao ->clear();
    khungSoanThao ->setFocus();
}

void CuaSoNguoiDungChu::anEnterGuiTin() {
    anNutGuiTin();
}

void CuaSoNguoiDungChu::nhanDuLieu() {

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


void CuaSoNguoiDungChu::ketNoi() {
    cuocHoiThoai->append(tr("<em>Kết nối thành công !</em>"));
    nutKetNoi->setEnabled(true);
}

void CuaSoNguoiDungChu::ngatKetNoi() {
    cuocHoiThoai->append(tr("<em>Tạm biệt, hẹn gặp lại sau !</em>"));
}


void CuaSoNguoiDungChu::loiSocket(QAbstractSocket::SocketError loi) {
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
void CuaSoNguoiDungChu::anEnter(){
    QString listuser="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listuser.txt";
    QString listusermoi="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt";
    ghiFileMoi(nickname->text(),listusermoi);
    QTextStream out(stdout);
    QFile file(listuser);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Ko Mo Duoc File, Vui Long Chon Lai File!!");

    }
    QString  line;
    int i=0;
    QTextStream in(&file);

    while (!in.atEnd()) {

        line= in.readLine();
        if(line==nickname->text()){
            i = 1 ;
        }


    }
    file.close();
    if(i!=1)
    {
    ghiFileTatCa(nickname->text(),listuser);
    }
    nickname->setEnabled(false);
    nutKetNoi->setEnabled(true);
    nutGuiTin->setEnabled(true);
}
void CuaSoNguoiDungChu::anNutKetNoi() {
    cuocHoiThoai->append(tr("<em>Đang kết nối...</em>"));
   QString listusermoi1="C:/Users/The Hung/Desktop/C++ SOCKET/CONFIG/listusermoi.txt";
   QString line=docFileTatCa(listusermoi1);


   if( line.size() !=0 ){
       cuocHoiThoai->append(tr("<em>Phòng Đã Có Chủ, Xin Mời Đi Phòng Khác</em>"));

   }

   else{
       nutKetNoi->setEnabled(false);
       socket->abort();
    socket->connectToHost(ipMayChu->text(), congMayChu->value());

}}
