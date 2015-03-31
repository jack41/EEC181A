// converting roi.m to roi.c
#pragma warning (disable : 4996)
# include <stdio.h>
# include <math.h>
# include "img2.h"
# include "demo.h"

//int img [480][640];
int binary[480][640];
int rows_Sum[480] = { 0 };
int binary_rows_Sum[480] = { 0 };
int cols_Sum[640] = { 0 };
int binary_cols_Sum[640] = { 0 };
int cols = 0;
int rows = 0;
int rows_level = 0;
int cols_level = 0;
int rows_index_beg, rows_index_end;
int cols_index_beg, cols_index_end;
int i = 0, j = 0;
int ROIimg[221][223];
//delcare a 28x28 2d array
int output[28][28];
int nn[784];

double Z3[10];
int answer=0;

//void resize(int width, int height, int )
//{
//
//}

void NeuralNetwork()
{
	int i, j, k;
	double sum;
	double Z1[200];
	double Z2[200];
	
	//apply the weight 1
	//Multiplication Logic
	for (i = 0; i < 200; i++) 
	{
			sum = 0;
			for (k = 0; k < 784; k++) {
				sum = sum + W1[i][k] * nn[k];
			}
			Z1[i] = sum;
		
	}

	for (j = 0; j < 200; j++)
	{
		Z1[j] = Z1[j] + B1[j];
	}


	double temp;
	//
	for (i = 0; i < 200; i++)
	{
		temp = exp(-Z1[i]);
		Z1[i] = 1 / (1 + temp);
	}

	//apply weight 2
	//Multiplication Logic
	for (i = 0; i < 200; i++) {
	
			sum = 0;
			for (k = 0; k < 200; k++) {
				sum = sum + W2[i][k] * Z1[k];
			}
			Z2[i] = sum;
	
	}

	for (i = 0; i< 200; i++)
	{
		Z2[i] = Z2[i] + B2[i];
	}

	for (i = 0; i < 200; i++)
	{
		temp = exp(-Z2[i]);
		Z2[i] = 1 / (1 + temp);
	}

	//apply weight 3
	//Multiplication Logic
	for (i = 0; i < 10; i++) {
	
			sum = 0;
			for (k = 0; k < 200; k++) {
				sum = sum + W3[i][k] * Z2[k];
			}
			Z3[i] = sum;
		
	}

	int max = Z3[0];
	
	for (i = 0; i < 10; ++i)
	{
		if (Z3[i] > max)
		{
			max = Z3[i];
			answer = i+1; //add one to the index because the index starts with 0
		}
	}

	
}


int main(){

	//add up the columns
	for (cols = 0; cols<640; cols++)
	{
		for (rows = 0; rows<480; rows++)
		{
			cols_Sum[cols] += img[rows][cols];
		}
		int y = 0;
	}
	
	//hardcoding the value only work for this sample
	//base on the sum come up with binary to find the index
	for (cols = 0; cols<640; cols++)
	{
		if (cols_Sum[cols]>107000)
		{
			binary_cols_Sum[cols] = 1;
		}
		else
		{
			binary_cols_Sum[cols] = 0;
		}
		int x = 0;
		
	}

	//find the index that has 0
	for (i = 0; i < 640; i++)
	{
		if (binary_cols_Sum[i] == 0)
		{
			cols_index_beg = i;
			break;
		}
		//int y = 0;
	}

	//scan for the end
	for (i = 639; i > 0; i--)
	{
		if (binary_cols_Sum[i] == 0)
		{
			cols_index_end = i;
			break;
		}
	}

	//add up the rows
	for (rows = 0; rows<480; rows++)
	{
		for (cols = 0; cols<640; cols++)
		{
			rows_Sum[rows] += img[rows][cols];
		}
		int k = 0;
	}

	//base on the sum come up with binary to find the index
	for (rows = 0; rows<480; rows++)
	{
		if (rows_Sum[rows]>130000)
		{
			binary_rows_Sum[rows] = 1;
		}
		else
		{
			binary_rows_Sum[rows] = 0;
		}

	}

	//scan for begin index
	for (j = 0; j < 480; j++)
	{
		if (binary_rows_Sum[j] == 0)
		{
			rows_index_beg = j;
			break;
		}
		
	}

	//scan for end index
	for (j = 479; j>0; j--)
	{
		if (binary_rows_Sum[j] == 0)
		{
			rows_index_end = j;
			break;
		}
	}
	
	//use the index to get the region of interest
	int sizeCol = cols_index_end - cols_index_beg;
	int sizeRow = rows_index_end - rows_index_beg;

	int **ROI;
	//dynamically allocate memory for ROI
	ROI = (int **)malloc(sizeof(int *)*sizeRow);

	// for each row, malloc space for its buckets and add it to 
	// the array of arrays
	for (i = 0; i < sizeRow; i++) {
		ROI[i] = (int *)malloc(sizeof(int)*sizeCol);
	}
	
	//initialze it to 0
	for (i = 0; i < sizeRow; i++) {
		for (j = 0; j < sizeCol; j++) {
			ROI[i][j] = 0;
		}
	}

/******************************************************************************************************************/
//store the ROI into the dynamically allocated 2d array (pointer to pointer)
	for (i = cols_index_beg; i<cols_index_end; i++)
	{
		for (j = rows_index_beg; j<rows_index_end; j++)
		{
			ROI[j - rows_index_beg][i - cols_index_beg] = img[j][i];
		}
	}


	//find the height of the image;

	int width = sizeCol;
	int height = sizeRow;

	//calculate the scale factor
	double scaleWidth = (double)28 / width;
	double scaleHeight = (double)28 / height;



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

	//resize function
	//value to store the index
	int x;
	int y;
	for (i = 0; i<28; i++)
	{
		for (j = 0; j<28; j++)
		{
			//x = round((i - 1)*(height - 1) / (scaleHeight*height - 1) + 1);
			//y = round((j - 1)*(width - 1) / (scaleWidth*width - 1) + 1);

			x = round((i*(height - 1) / 27));
			y = round((j*(width - 1) / 27) );
			//output will have the 28x28 dimensions of the image
			output[i][j] = ROI[x][y];
		}
	}


	//convert the 28x28 into 784x1
	for (i = 0; i < 28; i++)
	{
		for (j = 0; j < 28; j++)
		{
			nn[i * 28 + j] = output[j][i]; //swap the j and i because matlab multiplys differently
		}
	}

	NeuralNetwork(); //call the neural network function

	printf("%d\n", answer); //print the answer
	
	//deallocate the memory
	free(ROI);
	return 0;
}