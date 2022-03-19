#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void Stars(){
	printf("\n\t\t  ");
	for(int i=0;i<50;i++){
		printf("*");
	}
	printf("\n");
}
struct Node {
	int data;
	struct Node* next;
};
typedef struct Node* node;
node makeNode(int x){
	node tmp=new Node();
	tmp->data=x;
	tmp->next=NULL;
	return tmp;
}
int size(node a){
	int cnt=0;
	while(a!=NULL){
		cnt++;
		a=a->next;
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
void in(node a){
	Stars();
	printf("\t\t   ");
	while(a!=NULL){
		printf("%2d",a->data);
	    a=a->next;
	}
	Stars();
}
int tranCtoI( char c)
{
    return (int)c-48;
}
char tranItoC( int i){
	return (char)i+48;
}
void readFile(FILE*f,node &a){
	if (f==NULL){
		printf("ERROR\n");
	}
	else {
		printf("\t\t   Read file successfully!");
		char c;
	while ((c = fgetc(f)) != EOF)
    {
        if((int)c>47&&(int)c<58){
        	insertLast(a,tranCtoI(c));
		}
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
        printf("\t\t   Can not open this file");
	}
    else{
    	printf("\t\t   File is opened");
	}
	int h=size(a);
	for(int i=0;i<h;i++){
		fprintf(file,"%c",tranItoC(a->data));
		a=a->next;
	}
	printf("\n\t\t   Write to file successfully");
}
void Ptrinh (node a)
{
	int n=size(a);
	if(a==NULL){
			printf("\t\t   Error");
	}
	else {
		for(int i=0;i<n;i++){
		    int m=n-i-1;
	    	switch(i){
	    		case 0:
	    			printf("\t\t   %dx^%d",a->data,m);
	    	        break;
	    	    case 4:
	    	    	printf("+%dx",a->data);
	    	    	break;
	    	    case 5:
	            	printf("+%d",a->data);
	            	break;
		        default:
	    	    	printf("+%dx^%d",a->data,m);
	    	}
	    	a=a->next;
	    }
	}
}
int main(){
	FILE*f=fopen("INP.txt","r+");
	fseek(f,SEEK_SET,0);
	node a=NULL;
	while (1){
		Stars();
	    int c;
    	printf("\t\t   1. Read file.\n") ;
    	printf("\t\t   2. Delete element.\n") ;
    	printf("\t\t   3. Write data to file\n");
        printf("\t\t   4. Solve equation");
    	Stars();
    	printf("\t\t   Enter your selection:");
    	scanf("%d",&c);
    	switch(c){
    		case 1: 
    		    readFile(f,a);
    		    break;
    		case 2:
    			float n;
    			in(a);
	    		printf("\t\t   Nhap vi tri can xoa phan tu: ");
	    		scanf("%f",&n);
	    		deleteEle(a,n);
	    		in(a);
	    	    break;
	    	case 3:
	    		FILE *file;
                file = fopen("RESULT1.txt", "w");
	            writeToFile(file,a);
                fclose(file);
	    		break;  
	        case 4:
	    	    printf("\t\t   Phuong trinh can giai:\n");
	    	    Ptrinh(a);
	    	    break;
	    	default: printf("\t\t   ERROR!!!");
	}
	}
	
    fclose(f);
	return 0;
}
