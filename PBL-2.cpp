#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void Stars(){
	printf("\n");
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
            printf("vi tri xoa khong hop le");
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
	Stars();
	while(a!=NULL){
		printf("%d ",a->data);
	    a=a->next;
	}
	Stars();
}

void readFile(FILE*f,node &a){
	if (f==NULL){
		printf("ERROR\n");
	}
	else {
		printf("Read file successfully!");
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
        printf("Can not open this file");
	}
    else{
    	printf("File is opened");
	}
	int h=size(a);
	for(int i=0;i<h;i++){
		fprintf(file,"%d ",a->data);
		a=a->next;
	}
	printf("\nWrite to file successfully");
}

//float Try(node &a, int n, float &p1, float &p2){
//	int m2=abs(Get(a,0)), m1=abs(Get(a,1));
//	for(int i=1;i<n;i++){
//		if(m1<abs(Get(a,i+1))) m1=abs(Get(a,i+1));
//		if(m2<abs(Get(a,i))) m2=abs(Get(a,i));
//	}
//	p1=abs(Get(a,n))/(m2+abs(Get(a,n)));
//	p2=1+m1/abs(Get(a,0));
//}
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
//double PPChiaDoi(node &a, float p1, float p2, double eps){
//	double c;
//	double n=0;
//    do {
//        c = (p1 + p2) / 2;
//        
//		n=hoocner(a,c);
//        if ( n> 0) p2 = c;
//        else p1 = c;
//    }
//    while (fabs(p1 - p2) > eps && hoocner(a,c) != 0);
//    return c;
//}
bool autoCheck(node a,double n, double m){
	if(hoocner(a,n)*hoocner(a,m)<=0){
		return true;
	}
	return false;
}
double PPChiaDoi(node &a,double n, double m, double Epxilon){
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
	}
}
int main(){
	FILE*f=fopen("INP.txt","r+");
	fseek(f,SEEK_SET,0);
	node a=NULL;
	int chon ;
	do{
		printf("----------MENU----------\n");
		printf("1. Doc file.\n");
		printf("2. Xoa phan tu.\n");
		printf("3. Ghi file.\n");
		printf("4. Giai phuong trinh.\n");
		printf("0. Thoat. \n");
		printf("Enter your selection: ");
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
    			in(a);
	    		printf("Nhap vi tri can xoa phan tu: ");
	    		scanf("%f",&n);
	    		deleteEle(a,round(n/2));
	    		in(a);
				break;
			}
			break;
			case 3: {
				FILE *file;
                file = fopen("RESULT1.txt", "w");
	            writeToFile(file,a);
                fclose(file);
				break;
			}
			break;
			case 4: {
				double p=0,q=0,epx=0;
				int k;
	        	readFile(f,a);
	    	    printf("Phuong trinh can giai:\n");
	    	    Ptrinh(a);
	    	    printf("\nNhap sai so: ");
	    	    scanf("%lf",&epx);
	    	    printf("\n1.Nhap khoang nghiem");
	    	    printf("\n2.Tu dong chon khoang nghiem");
	    	    printf("\nEnter your selection: ");
		        scanf("%d", &k);
		        switch(k){
		        	case 1: {
		        		do {
                        printf("\nNhap khoang nghiem a, b: ");
                        printf("\n");
                        scanf("%lf %lf",&p,&q);
                        if (!autoCheck(a,p,q)) {
                        printf("\nKh nghiem sai, nhap lai!");
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
							p=-x1;
							q=-x2;
						}
						break;
					}
				}
				FILE *file2;
                file2 = fopen("RESULT2.txt", "w");
                Stars();
                printf("\n%lf", PPChiaDoi(a,p,q,epx));
                Stars();
                float h=PPChiaDoi(a,p,q,epx);
				fprintf(file2,"%f ",h);
				printf("\nGhi file thanh cong.");
				fclose(file2);
				break;
				break;
			}
			default:
				printf("Ket thuc chuong trinh");
				fclose(f);
	            return 0;
			break;
		}
		
		printf("\nBan co muon tiep tuc khong? (Nhap y/n)");
		char c ;
		fflush(stdin);
		scanf("%c", &c);
		if(c == 'y'){
			chon = -1; // gan chon khong phai la 1,2,3,0 thi chuong trinh se lap lai
		}else{
			printf("Tam biet!");
		}
		  
	}while(chon != 1 && chon != 2 && chon !=3 && chon!=0);
	fclose(f);
	return 0;
}
