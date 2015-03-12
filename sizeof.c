#include <stdio.h>

int main(void) {
	// your code goes here
	int img[28][28];
	int num = sizeof(img)/sizeof(img[0][0]);
	printf("%d\n", num);
	printf("result\n");
	
	return 0;
}
