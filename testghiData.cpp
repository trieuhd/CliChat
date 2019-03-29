#include<iostream>
#include<fstream>
using namespace std;
#include<string>
#include<ctime>
int main(){
	ofstream fileout;
	fileout.open("config/data.txt",ios::out);
	
	while(true){
	fflush(stdin);
	string user;
	cout<<"\nNhap ten tai khoan: ";
	getline(cin,user);
	fflush(stdin);
	string note;
	getline(cin, note);
	time_t baygio = time(0);
   tm *ltm = localtime(&baygio);

   fileout<<1900+ltm->tm_year<<"/"<<1+ltm->tm_mon<<"/"<<ltm->tm_mday<<" "<<ltm->tm_hour << ":"<<ltm->tm_min << ":"<<ltm->tm_sec <<"      "<<user<<"      "<<note<< endl;
   
	}
	fileout.close();
	system("pause");
	return 0;
}
