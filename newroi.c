// converting roi.m to roi.c
#pragma warning (disable : 4996)
# include <stdio.h>
int img [480][640];
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

int main(){


	

	FILE *file = fopen("./image1.txt", "r");
	if (file == NULL)
	{
		printf("ERROR!");
		exit(1);
	}

	//int y = 0;
	rows_level = 255 * 0.6;
	cols_level = 255 * 0.6;
	
	 //Generate image in an array
	for (rows = 0; rows < 480; rows++)
	 {
		 for (cols = 0; cols < 640; cols++) {
			fscanf(file, "%d", &img[rows][cols]);
			//printf("Rows: %d\n", rows);
			//printf("Columns: %d\n", cols);
			
		}
	}
	fclose(file);
	

//	 for (rows = 0; rows < 480; rows++)
//	{
//		for (cols = 0; cols < 640; cols++) {
//			if (img[rows][cols] > 160)
//			{
//				binary[rows][cols] = 1;
//			}
//			else
//			{
//				binary[rows][cols] = 0;
//			}
//		}
//	}
//
	//add up the columns
	for (cols = 0; cols<640; cols++)
	{
		for (rows = 0; rows<480; rows++)
		{
			cols_Sum[cols] += img[rows][cols];
		}

	}
	
	//hardcoding the value only work for this sample
	//base on the sum come up with binary to find the index
	for (cols = 0; cols<640; cols++)
	{
		if (cols_Sum[cols]>79000)
		{
			binary_cols_Sum[cols] = 1;
		}
		else
		{
			binary_cols_Sum[cols] = 0;
		}
	}

	//find the index that has 0
	for (i = 0; i < 640; i++)
	{
		if (binary_cols_Sum[i] == 0)
		{
			cols_index_beg = i;
		}
	}

	//scan for the end
	for (i = 639; i > 0; i--)
	{
		if (binary_cols_Sum[i] == 0)
		{
			cols_index_end = i;
		}
	}

	//add up the rows
	for (rows = 0; rows<480; rows++)
	{
		for (cols = 0; cols<640; cols++)
		{
			rows_Sum[rows] += img[rows][cols];
		}
	}

	//base on the sum come up with binary to find the index
	for (rows = 0; rows<480; rows++)
	{
		if (rows_Sum[rows]>89000)
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
		}
	}

	//scan for end index
	for (j = 479; j>0; j--)
	{
		if (binary_rows_Sum[j] == 0)
		{
			rows_index_end = j;
		}
	}
	
	//use the index to get the region of interest

	int sizeCol = cols_index_end - cols_index_beg;
	int sizeRow = rows_index_end - rows_index_beg;

	int ROIimg[] = {0};

	for (i = cols_index_beg; i<cols_index_end; i++) {
		for (j = rows_index_beg; j<rows_index_end; j++)
		{
			=img[j][i]);
			printf("%d ", img[rows][cols]);
		}
	}
	return 0;
}