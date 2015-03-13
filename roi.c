// converting roi.m to roi.c

# include <stdio.h>


int main(){

	FILE *file = fopen("image1.txt", "r");
	int img[480][640];
	int rows_sum[480] = {0};	// array with elements initialized to 0
	int cols_sum[640] = {0};
	int rows_binary[480] = {0};
	int cols_binary[640] = {0};
	int cols=0, rows=0;
	int cols_max = 0, cols_avg = 0;
	int rows_max = 0, rows_avg = 0;
	int rows_level = 0;
	int cols_level = 0;
	int rows_index_beg, rows_index_end;
	int cols_index_beg, cols_index_end;
	int i=0, j=0;
/*
	for (cols = 0; cols < 640; cols++) {
		printf("%d ", cols_sum[cols]);
	}
	
	printf("\n\n\n");
	for (rows = 0; rows < 640; rows++) {
		printf("%d ", rows_sum[rows]);
	}
*/
	// Generate image in an array
	// sum rows and cols in arrays
	for (cols = 0; cols < 640; cols++) {
		for (rows = 0; rows < 480; rows++) {
			fscanf(file, "%d", &img[rows][cols]);
		//	printf("Rows: %d\n", rows);
		//	printf("Columns: %d\n", cols);
			cols_sum[cols] += img[rows][cols];
			rows_sum[rows] += img[rows][cols];
		}
	}
	
	printf("%d ", img[120][120]);


//-------------------------------------------------------------------------------------
//		Get black ROI image
//-------------------------------------------------------------------------------------


	// Find row_max and col_max
	// Calculate row_avg and col_avg
	for (cols = 0; cols < 640; cols++) {
		
		cols_avg += cols_sum[cols];

		if (cols_max < cols_sum[cols])
			cols_max = cols_sum[cols];
	}
	cols_avg = cols_avg/640;
	
//	printf("%d\n", cols_avg);
//	printf("%d\n\n", cols_max);

	for (rows = 0; rows < 480; rows++) {

		rows_avg += rows_sum[rows];

		if (rows_max < rows_sum[rows])
			rows_max = rows_sum[rows];
	}
	rows_avg = rows_avg/480;

//	printf("%d\n", rows_avg);
//	printf("%d\n", rows_max);


	// Generate levels for im2bw
	cols_level = (cols_max + cols_avg)/2;
	rows_level = (rows_max + rows_avg)/2;

//	printf("%d\n", cols_level);
//	printf("%d\n", rows_level);

	// Make im2bw arrays
	// for cols
	for (cols = 0; cols < 640; cols++) {
		if (cols_level <= cols_sum[cols]){
			cols_binary[cols] = 1;
			printf("%d ", cols_binary[cols]);
		}
		else if (cols_level > cols_sum[cols]){		
			cols_binary[cols] = 0;
			printf("%d ", cols_binary[cols]);
		}
	}
	
	printf("\n\n\n");
		
	// for rows
	for (rows = 0; rows < 480; rows++) {
		if (rows_level <= rows_sum[rows]){
			rows_binary[rows] = 1;
			printf("%d ", rows_binary[rows]);
		}
		else if (rows_level > rows_sum[rows]){
			rows_binary[rows] = 0;
			printf("%d ", rows_binary[rows]);
		}
	}
	

	// Find the array where row_index == first part of black box
	// row_index(end) should be the end of the black box
	for (rows = 0; rows < 480; rows++) {
		if (rows_binary[rows] == 0 && rows_binary[rows-1] == 1){
			rows_index_beg = rows;
			}
			
	}

	for (rows = 480; rows > 0; rows--) {
		if (rows_binary[rows] == 0 && rows_binary[rows+1] == 1){
			rows_index_end = rows;
		}
			
	}


	// Find the array where col_index == first part of black box
	// col_index(end) should be the end of the black box 
	for (cols = 0; cols < 640; cols++) {
		if (cols_binary[cols] == 0 && cols_binary[cols-1] == 1){ // check if hit black box and
			cols_index_beg = cols;				// previous value was white
		}
	}

	for (cols = 640; cols > 0; cols--) {
		if (cols_binary[cols] == 0 && cols_binary[cols+1] == 1){
			cols_index_end = cols;
			}
	}


	fclose(file);
/*
	FILE *file2 = fopen("write1.txt", "w");
	if (file2 == NULL){
		printf("Error opening text file.\n");
		return(1);
	}


	// print img matrix array
	// should be just the black box with the digit
	for (i=cols_index_beg; i<cols_index_end; i++) {
	//	fprintf(file2,"\n");
		for (j=rows_index_beg; j<rows_index_end; j++) {
	//		fprintf(file2, "%d ", img[rows][cols]);
			printf("%d ", img[rows][cols]);
		}
	//	fprintf(file2,"\n");
	}
	
	fclose(file2);
*/
	
	printf("\n\n%d %d %d %d\n", cols_index_beg, cols_index_end, rows_index_beg, rows_index_end);

	return 0;
}
