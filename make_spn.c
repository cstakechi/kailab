#include<stdio.h>
#include<math.h>
#include"make_spn.h"

#define lm 16

void make_binary(int num,int array_binary[]){
	int i;
		for(i=0;i<4;i++){
				array_binary[3-i] = num % 2;
				num = num / 2;
			}
}

int pi_s[lm] = {0xE, 0x4, 0xD, 0x1,
               0x2, 0xF, 0xB, 0x8,
               0x3, 0xA, 0x6, 0xC,
               0x5, 0x9, 0x0, 0x7};

int pi_p[lm] = {  1,   5,   7,  13,
                 2,   6,  10,  14,
                 3,   7,  11,  15,
                 4,   8,  12,  16};


void pip(int w1[],int w2[], int w3[], int w4[],int p,int temp[]){
	p -= 1;
	w1[p] = temp[0];
	w2[p] = temp[1];
	w3[p] = temp[2];
	w4[p] = temp[3];
}




void spn(int a, int b, int c, int d, int cipher[]){

	int k[32]={0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1};
	int w1[4],w2[4],w3[4],w4[4];
	int u1[4],u2[4],u3[4],u4[4];
	int v1,v2,v3,v4;
	int temp[4];

	make_binary(a,w1);
	make_binary(b,w2);
	make_binary(c,w3);
	make_binary(d,w4);

	int i,round;
	for(round=0;round<3;round++){
		for(i=0;i<4;i++){
			u1[i] = w1[i] ^ k[i+(round*4)];
			u2[i] = w2[i] ^ k[i+4+(round*4)];
			u3[i] = w3[i] ^ k[i+8+(round*4)];
			u4[i] = w4[i] ^ k[i+12+(round*4)];
		}
		v1 = decimal(u1);
		v2 = decimal(u2);
		v3 = decimal(u3);
		v4 = decimal(u4);
		v1 = pi_s[v1];
		v2 = pi_s[v2];
		v3 = pi_s[v3];
		v4 = pi_s[v4];
		make_binary(v1,temp);
		pip(w1,w2,w3,w4,1,temp);
		make_binary(v2,temp);
		pip(w1,w2,w3,w4,2,temp);
		make_binary(v3,temp);
		pip(w1,w2,w3,w4,3,temp);
		make_binary(v4,temp);
		pip(w1,w2,w3,w4,4,temp);
	}

	for(i=0;i<4;i++){
		u1[i] = w1[i] ^ k[i+(round*4)];
		u2[i] = w2[i] ^ k[i+4+(round*4)];
		u3[i] = w3[i] ^ k[i+8+(round*4)];
		u4[i] = w4[i] ^ k[i+12+(round*4)];
	}
	round++;
	v1 = decimal(u1);
	v2 = decimal(u2);
	v3 = decimal(u3);
	v4 = decimal(u4);
	v1 = pi_s[v1];
	v2 = pi_s[v2];
	v3 = pi_s[v3];
	v4 = pi_s[v4];
	make_binary(v1,w1);
	make_binary(v2,w2);
	make_binary(v3,w3);
	make_binary(v4,w4);

	for(i=0;i<4;i++){
			u1[i] = w1[i] ^ k[i+(round*4)];
			u2[i] = w2[i] ^ k[i+4+(round*4)];
			u3[i] = w3[i] ^ k[i+8+(round*4)];
			u4[i] = w4[i] ^ k[i+12+(round*4)];
	}
	a = decimal(u1);
	b = decimal(u2);
	c = decimal(u3);
	d = decimal(u4);
	cipher[0] = a;
	cipher[1] = b;
	cipher[2] = c;
	cipher[3] = d;


}
