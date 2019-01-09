#include "stdio.h"
#include"conio.h"
#include <math.h>
struct nut{
	int info;
	int cb; //gia tri can bang: 0:ko lech; 1 lech trai; 2 lech phai
	nut *trai, *phai;
};
typedef nut Node;
Node *goc;

void Khoitao(Node*&goc){
	goc=NULL;
}

void Mocnut(Node*&goc,int x){
	if(goc==NULL){
	goc=new Node;
	goc->info=x;
	goc->phai=NULL;
	goc->trai=NULL;
	goc->cb=0;
	}
	else
	if(goc->info<=x) // gtri goc < x thi x >hon nen moc x qua ben phai
		Mocnut(goc->phai,x);
	else 
		Mocnut(goc->trai,x);
	
}

void Taocay(Node*&goc){
	int tam;
	do{
		printf("Nhap 1 so, 0:dung");
		scanf("%d",&tam);
		if(tam!=0)
		Mocnut(goc,tam);
	}while(tam!=0);
}


//cau3
void Xoaytrai(Node*&p){ // quaytrai p->trai, sau do quay ve th xoai phai
	Node*q;
	q=p->phai;
	p->phai=q->trai;
	q->trai=p;
	p=q;
}

void Xoayphai(Node*&p){ // xoay phai p
	Node*q;
	q=p->trai; // q la dinh can xoay
	p->trai=q->phai;
	q->phai=p;
	p=q;
				
}
void Canchinhtrai(Node*&p){
	switch(p->trai->cb){
	 
	case 1: // TH mat can bang Trai->Trai
		Xoayphai(p);
		p->cb=0;
		p->phai->cb=0;
		break;
	case 2: // TH mat can bang Trai->Phai
		Xoaytrai(p->trai);
		Xoayphai(p);
		switch(p->cb){
			case 0:
			 p->trai->cb=0;
			 p->phai->cb=0;
			 break;
			case 1:
			 p->trai->cb=0;
			 p->phai->cb=2;
			 break;
			case 2:
			 p->trai->cb=1;
			 p->phai->cb=0;
			 break;	
		}
		p->cb=0;
		break;
	}
}

void Canchinhphai(Node*&p){
	switch(p->phai->cb){
case 1: //Ghi chú: cho bi?t dây là tru?ng h?p m?t cân b?ng nào?
Xoayphai(p->phai);
Xoaytrai(p);
switch(p->cb){
case 0:
p->trai->cb= 0;
p->phai->cb= 0;
break;
case 1:
p->trai->cb= 1;
p->phai->cb= 0;
break;
case 2:
p->trai->cb= 0;
p->phai->cb= 2;
break;
}
p->cb = 0;
break;
case 2: //Ghi chú: cho bi?t dây là tru?ng h?p m?t cân b?ng nào?
Xoaytrai(p);
p->cb = 0;
p->trai->cb = 0;
break;
}
}

//----cau 5

//Tìm phan tu thay the
int Thaythe(Node *&p, Node *&q)
{ 
            int res;
            if (q->trai != NULL) 
            {
                        res = Thaythe(p, q->trai);
                        if (res < 2) 
                                    return res;
                        switch (q->cb)
                        {
                                    case 1: q->cb= 0;
                                                return 2;
                                    case 0: q->cb= 2;
                                                return 1;
                                    case 2:  Canchinhphai(q); 
                        }
            } else {
                        p->info = q->info;
                        p = q;
                        q = q->phai;
                        return 2;
            }
            delete q;
}   

//  Xoa nut
int deleteNode(Node *&T, int X)
{ 
    int res ; 
    if (T==NULL) 
        return 0; 
    if (T->info > X){ 
         res = deleteNode (T-> trai , X); 
         if ( res < 2) 
               return res ; 
          switch ( T-> cb ) { 
  			  case 1: T-> cb = 0; 
    		   return 2; 
              case 0: T-> cb = 2; 
                return 1; 
              case 2: Canchinhphai (T); 
                         } 
            } 
            else if (T->info < X) 
            { 
                res = deleteNode (T-> phai , X); 
              if ( res < 2) return res ; 
                 switch (T-> cb ){ 
           		  case 2: T-> cb = 0; 
                     return 2; 
                  case 0: T-> cb = 1; 
                     return 1; 
           		  case 1: Canchinhtrai (T); 
                         } 
            } 
            else // if (T->info == X) 
            { 
                         
             Node * p = T; 
                   if (T-> trai == NULL){ 
                       T = T->phai ; res = 2; 
                    } 
                    else 
					if (T-> phai == NULL) { 
                        T = T-> trai ; res = 2; 
                         } 
                     else // if (T-> trai != NULL && T-> phai != NULL) 
                         { 
                       res = Thaythe ( p, T -> phai ); 
                     if( res < 2) 
                             return res;
                               switch( T-> cb ) 
                                      { 
                                 case 2: T-> cb = 0; 
                                           return 2; 
                                 case 0: T-> cb = 1; 
                                            return 1; 
                                 case 1: Canchinhtrai (T); 
                                      } 
                         } 
                         delete p; 
        return res ; 
    } 
}




// cau 6 Kiem tra cay co phai la cay AVL

// Kiem tra cây nhi phân T có phai là "cây nhi phân cân bang hoàn toàn" hay không?
//cây nhi phân cân bang hoàn toàn là cây nhi phân tìm kiem mà tai moi nút cua nó 
//so nút cua cây con trái và cây con phai chêch lech ko quá 1
//0 là cây nhi phân tìm kiem
//1 ko phai là cây nhi phân tìm kiem
void TimMax(Node *c, int &Max)
{
    if (c==NULL)
        return ;
    if (c->trai != NULL)
        Max = (Max > c->trai->info)? Max : c->trai->info;
    if (c->phai != NULL)
        Max = (Max > c->phai->info)? Max : c->phai->info;
    Max = (Max > c->info) ? Max : c->info;
    TimMax(c->trai,Max);
    TimMax(c->phai,Max);
}
int DemNode(Node *c)
{
    if (c==NULL)
        return 0;
    int DemR = DemNode(c->phai);
    int DemL = DemNode(c->trai);
    return DemR + DemL + 1;
}

int KiemTra(Node *c)
{
    if (c==NULL)
        return 0;
    int Left = KiemTra(c->trai);
    //kiem tra dieu kien cua cây nhi phân tìm kiem
    int MaxL, MaxR;
    if (c->trai != NULL && c->phai != NULL)
    {
        TimMax(c->trai, MaxL);
        TimMax(c->phai, MaxR);
        if (!(MaxL < c->info && c->info < MaxR))
            return 1;
    }
    else if (c->trai == NULL && c->phai != NULL)
    {
        TimMax(c->phai, MaxR);
        if (!(c->info < MaxR))
            return 1;
    }
    else if (c->trai != NULL && c->phai == NULL)
    {
        TimMax(c->trai, MaxL);
        if (!(MaxL < c->info))
            return 1;
    }
    //kiem tra dieu kien cua cây nhi phân tìm kiem cân bang hoàn toàn
    int NodeR = DemNode(c->phai);
    int NodeL = DemNode(c->trai);
    printf ("\n node: %d lech Right: %d, Left: %d", c->info,NodeR,NodeL);
    if (abs(NodeR - NodeL) > 1)    //chêch lech lon hon 1
        return 1;
    int Right = KiemTra(c->phai);
    return Left + Right;
}
void XuatKqKiemTra(Node *c)
{
    int Kt = KiemTra(c);
    if (Kt == 0)
        printf("\nla cay nhi phan tim kiem can bang hoan toan");
    else
        printf("\nko phai cay nhi phan tim kiem can bang hoan toan");
}

int main(){
	Khoitao(goc);
	Taocay(goc);
	deleteNode(goc,2);
	XuatKqKiemTra(goc);
	
	
 getch();
}
