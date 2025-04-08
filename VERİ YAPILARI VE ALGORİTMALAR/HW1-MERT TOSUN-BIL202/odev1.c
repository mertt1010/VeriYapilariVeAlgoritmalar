#include <stdio.h>
#include <stdlib.h>
#include "p1-05.c"

int compare (void* ptr1, void* ptr2);
int main (void)
{
	int i = 7;
	int j = 8;
	int lgr;

	lgr = (*(int*) larger (&i, &j, compare));

	printf("larger value is: %d\n", lgr);
}

int compare (void* ptr1, void* ptr2)
{
	if(*(int*)ptr1 >= *(int*)ptr2)
		return 1;
	else
		return -1;
}
