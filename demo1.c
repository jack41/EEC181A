#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "demo.h"

//volatile int * Start      = (int * )0xFF200070;
//volatile int * Stop      = (int * )0xFF200030;
//volatile int * Rin      = (int * )0xFF200040;
//volatile int * Gin      = (int * )0xFF200050;
//volatile int * Bin      = (int * )0xFF200060;
//volatile int * Rout      = (int * )0xFF200010;
//volatile int * Gout     = (int * )0xFF200020;
//volatile int * Bout      = (int * )0xFF200030;
//volatile int * fVal      = (int * )0xFF200000;

//volatile int * SDRAMCLK_Select      = (int * )0xFF200010;
//volatile int * Ready     = (int * )0xFF200020;

void delay(int v) {
	int c, d;
	int max;
	max = 1000 * v;
	for(c = 1; c <= max; c++)
		for(d = 1; d <= 327; d++)
		{}
	return 0;
}


//resize function using the nearest neighbor
//be sure to include <math.h>
void resize(int image)
{
	int img[][] = { { 0 }, { 0 } };
	//assume this is our image

	//find the height of the image;

	int width;
	int height;

	//calculate the scale factor
	double scaleWidth = 28 / width;
	double scaleHeight = 28 / height;

	//delcare a 28x28 2d array
	int output[28][28];

	//initialize the 2d array with 0
	int i, j;
	for (i = 0; i<28; i++)
	{
		for (j = 0; j<28; j++)
		{
			output[i][j] = 0;
		}
	}

	//calculate the max index for the for loop
	double widthMax = scaleWidth*width;
	double heightMax = scaleHeight*height;

	//value to store the index
	int x;
	int y;
	for (i = 1; i<heightMax; i++)
	{
		for (j = 1; j<widthMax; j++)
		{
			x = round((i - 1)*(height - 1) / (scaleHeight*height - 1) + 1);
			y = round((j - 1)*(width - 1) / (scaleWidth*width - 1) + 1);

			//output will have the 28x28 dimensions of the image
			output[i][j] = img[x][y];
		}
	}

}


void NeuralNetwork(int img)
{
	int i, j, k;
	int sum;
	int Z1[200][1];
	int Z2[200][1];
	int Z3[10][1];
	//apply the weight 1
	//Multiplication Logic
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 1; j++) {
			sum = 0;
			for (k = 0; k < 784; k++) {
				sum = sum + W1[i][k] * img[k][j];
			}
			Z1[i][j] = sum;
		}
	}

	double temp;
	//
	for (i = 0; i < 200; i++)
	{
		temp = exp(Z1[i][1]);
		Z1[i][1] = 1 / (1 + temp);
	}

	//apply weight 2
	//Multiplication Logic
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 1; j++) {
			sum = 0;
			for (k = 0; k <= 200; k++) {
				sum = sum + W2[i][k] * Z1[k][j];
			}
			Z2[i][j] = sum;
		}
	}

	for (i = 0; i < 200; i++)
	{
		temp = exp(Z2[i][1]);
		Z2[i][1] = 1 / (1 + temp);
	}

	//apply weight 3
	//Multiplication Logic
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 1; j++) {
			sum = 0;
			for (k = 0; k <= 200; k++) {
				sum = sum + W3[i][k] * Z2[k][j];
			}
			Z3[i][j] = sum;
		}
	}

	double swap;

	//use bubble sort to sort the array
	//answer is the the first element of the array
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10-1; i++)
		{
			if (Z3[i][1] < Z3[i+1][1]) /* For decreasing order use < */
			{
				swap = Z3[i][1];
				Z3[i][1] = Z3[i + 1][1];
				Z3[i + 1][1] = swap;
			}
		}
	}
}

int main(){
	int test = 0;
	//double firstVal = -2.6391;
	//*(Start) =number1;
//	*(Stop) = 0;
//	*(SDRAMCLK_Select) = 1;
//	*(Ready) = 1;

	if (W1[0][783] == 0.000221125)
	{
		test = 11;
	}
	printf("print test value %d \n", test);

	int i = 0;
	while (i < 200)
	{
		printf("%f", W3[0][i]);
		i++;
	}
	return 0;
}
