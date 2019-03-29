#include<iostream>
#include<fstream>
using namespace std;
#include<string>
struct acc{
	string user;
	string pass;
};
typedef struct acc account;
struct NODE{
	account data;
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
NODE *MakeNode(account &sv){
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

void doc1hang(ifstream &filein,account &sv){
	getline(filein,sv.user,' ');
	getline(filein,sv.pass);
}
void doctatcahang(ifstream &filein,list &l){
	while(!filein.eof()){
		account sv;
		doc1hang(filein,sv);
		node *p=MakeNode(sv);
		themcuoi(p,l);
	}	
}
void xuat_1_hang(account sv){
	cout<<"\nHO TEN: "<<sv.user;
	cout<<"\nDIEM: "<<sv.pass;
}
void xuat_danh_sach(list &l){
	int i=0;
	for(node *p=l.pHead;p!=NULL;p=p->pNext){
		i++;
		cout<<"\n\n\t\tHOC SINH THU "<< i;
		xuat_1_hang(p->data);
	}
}

void timvitri(account acc,list l){
	int i=0;
		for(node *p=l.pHead;p!=NULL;p=p->pNext){
			if(acc.user==p->data.user){
				if(acc.pass==p->data.pass) cout<<"\nTon Tai";
				else cout<<"\nPass sai";
				
				i++;
			}
			
		}
		
		if(i==0){
			cout<<"\nSai tai khoan hoac mat khau";
		}

}

int main(){
	ifstream filein;
	filein.open("config/listuser.txt",ios::in);
	list l;
	KhoiTaoList(l);
	doctatcahang(filein,l);
	xuat_danh_sach(l);
	fflush(stdin);
	filein.close();
	cout<<"\n";
	account acc1;
	cout<<"\nNhap user: ";
	getline(cin,acc1.user);
	cout<<"\nNhap pass: ";
	getline(cin,acc1.pass);
	timvitri(acc1,l);
	
	system("pause");
	return 0;
}
