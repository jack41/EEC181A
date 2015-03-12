//resize function using the nearest neighbor
//be sure to include <math.h>
#include <math.h>

void resize(int img[][])
{
	//int img[][]; 
	//assume this is our image
	
	//find the height of the image;
	
	int width;
	int height;
	
	//calculate the scale factor
	double scaleWidth = 28 /width;
	double scaleHeight = 28 /height;
	
	//delcare a 28x28 2d array
	int output[28][28];
	
	//initialize the 2d array with 0
	int i, j;
	for (i=0; i<28; i++)
	{
		for(j=0; j<28; j++
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
	for(i=1; i<heightMax; i++)
	{
		for(j=1; j<widthMax; j++)
		{
			x = round((i-1)*(height-1)/(scaleHeight*height-1)+1);
			y = round((j-1)*(width-1)/(scaleWidth*width-1)+1);
			
			//output will have the 28x28 dimensions of the image
			output[i][j] = img[x][y];
		}
	}
	
}
	
	
	
}