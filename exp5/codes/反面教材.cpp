#include<stdio.h>
#include<stdlib.h>
#define MAX 4096
#define INTMAX 4294967295

unsigned int hashtab[MAX]={0};

int h(unsigned long long int x);
int hash(unsigned long long int a);

int main(){
	unsigned long long int a;
	int b, i, c, yes=0, no=0, yesn=0, non=0;
	for(i=1;i<=10000;i++){
		scanf("%u %d", &a, &b);
		c = hash(a);
		if(b){//insert
			int j = 1;
			while((hashtab[c]!=0)&&(hashtab[c]!=INTMAX)){
				c = (c+h(a))%MAX;
				j++;	
			}
			hashtab[c]=a;
			printf("%d %d\n",j,c);
		}
		else{
			int j=1;
			int t=0;
			while(hashtab[c]){
				if(hashtab[c] == a) {
					t = 1;
					break;
				}
				c = (c+h(a))%MAX;
				j++;
			}
			if(t){
				hashtab[c]=INTMAX;
				printf("%d %d\n", j, c);
				yes += j;
				yesn++;
			}
			else{
				printf("%d -1\n", j);
				no += j;
				non++;
			}	 
		}
	}
	printf("%d/%d\n", yes,yesn);
	printf("%d/%d\n", no, non);
}

int h(unsigned long long int x){
	unsigned long long int y;
	if(x%2==1) y = x % MAX;
	else y = (x+1) % MAX;
	return (int)y;
}

int hash(unsigned long long int a){
	unsigned long long int b = a;
	unsigned long long int c = (b*b % 274877906944 - b*b % 67108864) / 67108864;
	return (int)c;
}