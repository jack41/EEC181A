#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "lab6.h"

volatile int * Start      = (int * )0xFF200080;
volatile int * Stop      = (int * )0xFF200010;
//volatile int * Rin      = (int * )0xFF200040;
//volatile int * Gin      = (int * )0xFF200050;
//volatile int * Bin      = (int * )0xFF200060;
//volatile int * Rout      = (int * )0xFF200010;
//volatile int * Gout     = (int * )0xFF200020;
//volatile int * Bout      = (int * )0xFF200030;
volatile int * oMuxSel      = (int * )0xFF200000;
//volatile int * Address = (int * )0x00000000;
volatile int * iData = (int * )0xFF200060;

volatile int * DDR3			= (int *) 0x0010000; // Up to 0xFFF0000

int image[480][640];
int word_offset;


void delay(int v) {
	int c, d;
	int max;
	max = 1000 * v;
	for(c = 1; c <= max; c++)
		for(d = 1; d <= 327; d++)
		{}
	return 0;
}


int main(){

	printf("Start\n");
	int test = 0;
	int temp;
	*(Start) =1;
	delay(50);
	*(Stop) = 0; //take a snapshot
	int i, j, k;
	 for (i = 0; i < 307200; i++)	// 640x480
	 {
	 	*oMuxSel = 1;
	
		//*oMuxSel = 1;
		//*oMuxSel = 0;
		*(DDR3) =  *(iData);
		*(DDR3)++;
		*oMuxSel = 0;
	 }
	*(Start) =1;
	
	for (i = 0; i <480; i++)
	{
		for (j = 0; j < 640; j)
		{
			for (k = 0; k < 4; k++)
			{
				image[i][j] = *(DDR3);
				*(DDR3)++;
				//word_offset+=4;
	
			}
		}
	}

	//int tempImage[307200];
	////image[y][x]
	//int image[480][640];

		//printf("start ? \n ");
		//scanf("%d", &temp);
		//if(temp==1)
		//{
		//	*(Start) =1;
		//	*(Stop)=0;
		//}else 
		//{
		//	*(Start) =0;
		//	*(Stop)=1;
		//}
		//
		//printf("start ? \n ");
		//scanf("%d", &temp);
		//if(temp==1)
		//{
		//	*(Start) =1;
		//	*(Stop)=0;
		//}else 
		//{
		//	*(Start) =0;
		//	*(Stop)=1;
		//}
		//
		//int i, j;
		//
		//for (i=0; i<307200; i++)
		//{
		//	tempImage[i] = Address + i;
		//}
		//
		//for (i=0; i<480; i++)
		//{
		//	for (j=0; j<640; j++)
		//	{
		//		image[i][j]=tempImage[i*640 + j];
		//	}
		//}
		//
		for (i=0; i<480; i++)
		{
			for (j=0; j<640; j++)
			{
				printf("%d\t", image[i][j]);
			}
			printf("\n");
		}
		
	printf("Done\n");

	
	return 0;
}