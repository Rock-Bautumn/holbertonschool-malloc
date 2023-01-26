#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	char *string;
	char *string2;
	
	string = _malloc(10);
	string2 = _malloc(19);
	printf("string address = %p\n", (void *) string);
	printf("string2 address = %p\n", (void *) string2);

	strcpy(string, "Holberton");
	strcpy(string2, "This is an example");
	printf("string = %s\n", string);
	printf("string2 = %s\n", string2);
	



	return (EXIT_SUCCESS);
}
