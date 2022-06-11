#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int kmax=1000;
void pr(){
	printf("\n");
	printf("\t");
	for(int i=0;i<24;i++){
		printf("-");
	}
	printf("\n");
}
struct Node {
	int data;
	struct Node* next;
};

typedef struct Node* node;
node makeNode(int x){
	node tmp; 
    tmp = (node)malloc(sizeof(struct Node)); 
	tmp->data=x;
	tmp->next=NULL;
	return tmp;
}
int size(node a){
	int cnt=0;
	node p;
	p=a;
	while(p!=NULL){
		cnt++;
		p=p->next;
	}
	return cnt;
}
bool empty(node a){
	return a==NULL;
}
void insertFirst(node &a,int x){
	node tmp=makeNode(x);
	if(empty(a)){
		a=tmp;
	}
	else{
		tmp->next=a;
		a=tmp;
	};
}
void insertLast(node &a,int x){
	node tmp=makeNode(x);
	if (empty(a)){
		a=tmp;
	}
	else{
		node p=a;
		while(p->next!=NULL){
			p=p->next;
		}
		p->next=tmp;
	}
}
void insetMiddle(node &a,int x,int pos){
	if(pos == 0 || a == NULL){
        insertFirst(a,x);
    }else{
        int k = 1;
        node p = a;
        while(p != NULL && k != pos){
            p = p->next;
            ++k;
        }
 		if(k != pos){
            insertLast(a, x);
        }else{
            node temp = makeNode(x);
            temp->next = p->next;
            p->next = temp;
        }
    }
}
void deleteFirst(node &a){
	if(a==NULL) return;
	else {
		a=a->next;
	}
}
void deleteLast(node &a){
	if(a==NULL) return ;
	else {
		node trc=NULL, sau=a;
		while(sau->next!=NULL){
			trc=sau;
			sau=sau->next;
		}
		if(trc==NULL){
			a=NULL;
		}
		trc->next=NULL;
	}
}
void deleteMiddle(node &a,int pos){
	if(pos == 0 || a == NULL || a->next == NULL){
        deleteFirst(a); 
    }else{
        int k = 1;
        node p = a;
        while(p->next->next != NULL && k != pos){ // truong hop xoa o vi tri null
            p = p->next;
            ++k;
        }
 
        if(k != pos){
            printf("\tVi tri xoa khong hop le");
        }else{
            p->next = p->next->next;
        }
    }
}
int Get(node &a, int index){
    int k = 0;
    node p = a;
    while(p->next != NULL && k != index){
        k++;
        p = p->next;
    }
    return p->data;
}
void in(node a){
	pr();
	printf("\t");
	while(a!=NULL){
		printf("%d ",a->data);
	    a=a->next;
	}
	pr();
}

void readFile(FILE*f,node &a){
	if (f==NULL){
		printf("\tERROR\n");
	}
	else {
		printf("\n");
		printf("\tRead file successfully!");
		while (feof(f) == 0)
    	{	
    		int n;
			fscanf(f,"%d",&n);
			insertLast(a,n);
    	}
    	in(a);
	}
}
void deleteEle(node &a,float n){
	int i=round(n);
	deleteMiddle(a,i);
}
void writeToFile(FILE *file,node a){
	if (!file){
        printf("\tCan not open this file");
	}
    else{
    	printf("\tFile is opened");
	}
	int h=size(a);
	for(int i=0;i<h;i++){
		fprintf(file,"%d ",a->data);
		a=a->next;
	}
	printf("\n\tWrite to file successfully");
}
double hoocner (node a,float b){
	float p=0;
	int j=size(a);
	for(int i=1;i<=j;i++){
		p=p*b+a->data;
		a=a->next;
	}
	return p;
}
bool check(node a,float c){
	if(hoocner(a,c)>0){
		return 1;
	}
	else {
		return 0;
	}
}
bool autoCheck(node a,double n, double m){
	if(hoocner(a,n)*hoocner(a,m)<=0){
		return true;
	}
	return false;
}
double PPChiaDoi(node &a,double n, double m, double Epxilon,int &t){
	   double c=(m+n)/2, E = fabs(n-m);
   while(E>Epxilon){
      if(hoocner(a,n)*hoocner(a,c)<=0)
         m = c;
      else
         n = c;
      E = fabs(m -n);
      c = (m + n)/2;
   }
   return c;
}
double PPDayCung(node &a,double n, double m, double Epxilon){
	double fn = hoocner(a,n) , fm = hoocner(a,m); 
	double x = n-(m-n)*fn/(fm-fn) , E = fabs(n-m);
   while(E>Epxilon){
      if(hoocner(a,n)*hoocner(a,x)<=0)
         m = x;
      else
         n=x;
      x = n-(m-n)*fn/(fm-fn) ;
      E = fabs(m -n);
      fn = hoocner(a,n) ;
	  fm = hoocner(a,m); 
   }
   return x;
}
void find(node a,float &x1,float &x2){
	float m1=0,m2=0,m=0;
	node h=a,k=a;
	h=h->next;
	int n=size(a);
	for(int i=1;i<n-1;i++){
		if(m<abs(h->data)){
			m=abs(h->data);
		}
		h=h->next;
	}
	if (m<abs(h->data)){
		m1=abs(h->data);
	}
	else {
		m1=m;
	}
	if (m<abs(a->data)){
		m2=abs(a->data);
	}
	else {
		m2=m;
	}
	float t=0;
	t=abs(h->data);
	x1=t/(m2+t);
	x2=1+(m1/(k->data));
}
void Ptrinh (node a)
{
	int n=size(a);
	if(a==NULL){
			printf("Error");
	}
	else {
		printf("\n\t");
		for(int i=0;i<n;i++){
		    int m=n-i-1;
		    if (a->data==0) {
		    	a=a->next;
		    	continue;
			}
		    if(m==n-1) {
		    	printf("%dx^%d",a->data,m);
		    	a=a->next;
		    	continue;
			}
			if (a->data>=0){
				switch(m){
	    	        case 1:
	    	    	    printf("+%dx",a->data);
	    	    	    break;
	    	        case 0:
	                	printf("+%d",a->data);
	                	break;
		            default:
	    	        	printf("+%dx^%d",a->data,m);
	        	}
			}
	    	else {
	    		switch(m){
	    	        case 1:
	    	        	printf("%dx",a->data);
	    	        	break;
	    	        case 0:
	                	printf("%d",a->data);
	                	break;
		            default:
	    	        	printf("%dx^%d",a->data,m);
	        	}
			}
			a=a->next;
	    }
	    printf("=0");
	}
}
int Menu (FILE*f,node &a){
	int chon;
	do{
		printf("\t----------MENU----------\n");
		printf("\t1. Doc file.\n");
		printf("\t2. Xoa phan tu va ghi file.\n");
		printf("\t3. Giai phuong trinh.\n");
		printf("\t0. Thoat. \n");
		printf("\tEnter your selection: ");
		scanf("%d", &chon);
		
		switch(chon){
			case 1: {
				readFile(f,a);
				break;
			}
			break;
			case 2: {
				readFile(f,a);
				float n;
	    		printf("\tNhap N de xoa phan tu o vi tri N/2: ");
	    		scanf("%f",&n);
	    		deleteEle(a,round(n/2));
	    		in(a);
	    		FILE *file;
                file = fopen("RESULT1.txt", "w");
	            writeToFile(file,a);
                fclose(file);
				break;
			}
			case 3: {
				double p=0,q=0,epx=0,x=0;
				int k,l,t;
				if (empty(a)){
					printf("\t404 NOT FOUND");
				}
				else {
	    	        printf("\tPhuong trinh can giai:\n");
	    	        Ptrinh(a);
	    	        printf("\n\tNhap sai so: ");
	    	        scanf("%lf",&epx);
	    	        printf("\n\t1.Nhap khoang nghiem");
	    	        printf("\n\t2.Tu dong chon khoang nghiem");
	    	        printf("\n\tEnter your selection: ");
		            scanf("%d", &k);
		            switch(k){
		            	case 1: {
		            		do {
                                printf("\n\tNhap khoang nghiem a, b: ");
                                scanf("%lf %lf",&p,&q);
                                if (!autoCheck(a,p,q)) {
                                    printf("\n\tKh nghiem sai, nhap lai!");
                                }
                                else break;
                            }
                            while (true);
					    	break;
				    	}
				    	case 2: {
				    		float x1,x2;
				    		find(a,x1,x2);
				    		if(autoCheck(a,x1,x2)){
				    			p=x1;
				    			q=x2;
				    		}
			    			else {
			    				if(autoCheck(a,-x1,-x2)){
			    					p=-x1;
			    				    q=-x2;
								}
			    				else {
			    					printf("\tKhong tim thay khoang nghiem");
			    					do {
                                        printf("\n\tNhap khoang nghiem a, b: ");
                                        scanf("%lf %lf",&p,&q);
                                        if (!autoCheck(a,p,q)) {
                                            printf("\n\tKh nghiem sai, nhap lai!");
                                        }
                                        else break;
                                    }
                                    while (true);
								}
			    			}
			    			break;
			    		}
			    	}
			    	FILE *file2;
                    file2 = fopen("RESULT2.txt", "w");
                    printf("\n\t1.Phuong phap chia doi");
                    printf("\n\t2.Phuong phap day cung");
                    printf("\n\tEnter your selection: ");
                    scanf("%d", &l);
                    switch(l){
                    	case 1: {
                    		pr();
                    		x=PPChiaDoi(a,p,q,epx,t);
                    		if(t ==1) printf("\tso lan lap qua lon");
                    		else printf("\n\t%lf",x);
                    		pr();
			    			break;
			    		}
			    		case 2:{
                            pr();
                            x=PPDayCung(a,p,q,epx);
			    		    printf("\n\t%lf",x);
                            pr();
			    			break;
			    		}
			    		default:
			    			printf("\tERROR");
			    			return 0;
			    	}
		    		fprintf(file2,"%f ",x);
		    		printf("\n\tGhi file thanh cong.");
		    		fclose(file2);
		    		break;
		        }
			    break;
			}
			default:
				printf("\tKet thuc chuong trinh");
				fclose(f);
	            return 0;
			break;
		}
		
		printf("\nBan co muon tiep tuc khong? (Nhap y/n) ");
		char c ;
		fflush(stdin);
		scanf("%c", &c);
		if(c == 'y'){
			chon = -1; // gan chon khong phai la 1,2,3,0 thi chuong trinh se lap lai
		}else{
			printf("\tTam biet!");
			break;
		}
		  
	}while(chon != 1 && chon != 2 && chon !=3 && chon!=0);
}
int main(){
	FILE*f=fopen("INP.txt","r+");
	fseek(f,SEEK_SET,0);
	node a=NULL;
	Menu(f,a);
	fclose(f);
	return 0;
}
