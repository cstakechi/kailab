#include<stdio.h>
#include<math.h>

	int a[8] = {1,1,0,0,1,0,1,0};
	int c[8] = {1,1,0,0,0,1,1,0};


void fieldinv(int *a){

	int temp,i;

	for(i=0;i<4;i++){
		temp = *(a+i);
		*(a+i) = *(a+7-i);
		*(a+7-i) = temp;
	}
}


int binarytofield(int a[]){
	int z=0,i;
	for(i=0;i<8;i++)
		z += a[i] * pow(2,i);
	return z;
}

void fieldtobinary(int z,int a[]){
	int i;
		for(i=0;i<8;i++){
				a[8-i] = z % 2;
				z = z / 2;
			}
}



int main(){

	int *p;
	int b[8];
	int z;
	int i,j;

	p = a;
	z = binarytofield(p);
	printf("%x\n",z);
	if(z != 0)
		fieldinv(a);

	for(i=0;i<8;i++){
		b[i] = a[i] + c[i];

		j = (i+4) % 8;
		b[i] +=  a[j];

		j = (i+5) % 8;
		b[i] += a[j];

		j = (i+6) % 8;
		b[i] += a[j];

		j = (i+7) % 8;
		b[i] += a[j];

		b[i] %= 2;

	}

	for(i=7;i>-1;i--)
		printf("%d",b[i]);

	return 0;
}
