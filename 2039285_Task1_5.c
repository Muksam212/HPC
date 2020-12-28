#include<stdlib.h>
#include<stdio.h>

int main(){
	int A=1, B=2, C=4, D=5;
	C=B+D;
	B=C+D;
	B=A+C;
	
	printf("B=%d,C=%d\n", B,C );
}
