#include<iostream>
#include<fstream>
using namespace std;
#include<string>
struct his{
	string ngay;
	string gio;
	string user;
	string note;
};
typedef struct his history;

struct NODE{
	history data;
	struct NODE *pNext;
};
typedef struct NODE node;
struct LIST{
	node *pHead;
	node *pTail;
};
typedef struct LIST list ;
void KhoiTaoList(LIST &l){
	l.pHead=NULL;
	l.pTail=NULL;
}
NODE *MakeNode(history &sv){
	NODE *p=new NODE;
	p->data=sv;
	p->pNext=NULL;
	return p;
}
void themcuoi(node *p,list &l){
	if(l.pHead==NULL){
		l.pHead=l.pTail=p;
	}
	else{
		l.pTail->pNext=p;
		l.pTail=p;
	}
}

void doc1hang(ifstream &filein,history &sv){
	getline(filein,sv.ngay,' ');
	getline(filein,sv.gio,' ');
	getline(filein,sv.user,' ');
	getline(filein,sv.note);
}
void doctatcahang(ifstream &filein,list &l){
	while(!filein.eof()){
		history sv;
		doc1hang(filein,sv);
		node *p=MakeNode(sv);
		themcuoi(p,l);
	}	
}
void xuat_1_hang(history sv){
	cout<<sv.gio<<" "<<sv.user<<" "<<sv.note;
}
void xuat_danh_sach(list &l){
	int i=0;
	for(node *p=l.pHead;p!=NULL;p=p->pNext){
		i++;
		cout<<"\n\n\t\tDong chat THU "<< i<<endl;
		xuat_1_hang(p->data);
	}
}


int main(){
	ifstream filein;
	filein.open("config/data.txt",ios::in);
	list l;
	KhoiTaoList(l);
	doctatcahang(filein,l);
	xuat_danh_sach(l);
	system("pause");
	return 0;
}
