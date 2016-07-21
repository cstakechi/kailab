#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "make_spn.h"

#define T 8000
void binary(int num,int array_binary[]){ //二進数へ変換
	int i;
	for(i=0;i<4;i++){
			array_binary[3-i] = num % 2;
			num = num / 2;
		}
}
int decimal(int array_binary[]){  //10進数へ変換
	int i,temp=0;
	for(i=0;i<4;i++)
		temp += array_binary[i] * pow(2,3-i);
	return temp;
}

int pi_s_im(int num){ //p_s^{-1}
	switch (num){
	case 0:
		return 0xe;
	case 1:
		return 0x3;
	case 2:
		return 0x4;
	case 3:
		return 0x8;
	case 4:
		return 0x1;
	case 5:
		return 0xc;
	case 6:
		return 0xa;
	case 7:
		return 0xf;
	case 8:
		return 0x7;
	case 9:
		return 0xd;
	case 0xa:
		return 0x9;
	case 0xb:
		return 0x6;
	case 0xc:
		return 0xb;
	case 0xd:
		return 0x2;
	case 0xe:
		return 0x0;
	case 0xf:
		return 0x5;
	default:
		return 100;
	}
}

int main(){

	int i,j,k;
	int count[16][16];
	int plaintext[4],ciphertext[4];
	int plaintext_binary[4][4],ciphertext_binary[4][4];
	int v2[4],v4[4];
	int u2,u4;
	int u2_binary[4],u4_binary[4];
	int temp[4];
	int z;
	int t;
	int maxkey1,maxkey2;

	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			count[i][j] = 0;

	for(t=0;t<T;t++){
		for(i=0;i<4;i++)
			plaintext[i] = rand()%16;

		spn(plaintext[0],plaintext[1],plaintext[2],plaintext[3],ciphertext);
		for(i=0;i<4;i++){
				binary(plaintext[i],plaintext_binary[i]);
		}
		for(i=0;i<4;i++)
			binary(ciphertext[i],ciphertext_binary[i]);

		for(i=0;i<16;i++){
			for(j=0;j<16;j++){
			//v_2の作成
				binary(i,temp);
				for(k=0;k<4;k++)
					v2[k] = temp[k] ^ ciphertext_binary[1][k];
			//v_4の作成
				binary(j,temp);
				for(k=0;k<4;k++)
					v4[k] = temp[k] ^ ciphertext_binary[3][k];
			//u2の作成
				u2 = decimal(v2);
				u2 = pi_s_im(u2);
			//u4の作成
				u4 = decimal(v4);
				u4 = pi_s_im(u4);
				binary(u2,u2_binary);
				binary(u4,u4_binary);
			//zの計算
				z = plaintext_binary[1][0] ^ plaintext_binary[1][2] ^ plaintext_binary[1][3] ^ u2_binary[1] ^ u2_binary[3] ^ u4_binary[1] ^ u4_binary[3];
				if(z == 0)
					count[i][j]++;
			}
		}
	}

	int max = -1;
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			count[i][j] = count[i][j] - (t / 2);
			if(count[i][j] < 0)
				count[i][j] = -count[i][j];
			if(count[i][j] > max){
				max = count[i][j];
				maxkey1 = i;
				maxkey2 = j;
			}
		}
	}
	printf("%x %x\n",maxkey1,maxkey2);
	return 0;
}
