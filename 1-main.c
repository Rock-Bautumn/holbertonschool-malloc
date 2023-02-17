#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main()
{
	char *string;
	char *string2;
	char *string3;
	
	string = _malloc(10);
	string2 = _malloc(19);
	string3 = _malloc(14);

	printf("string address = %p\n", (void *) string);
	printf("string2 address = %p\n", (void *) string2);
	printf("string3 address = %p\n", (void *) string3);

	strcpy(string, "Holberton");
	strcpy(string2, "This is an example");
	strcpy(string3, "A bad example");
	
	printf("string = %s\n", string);
	printf("string2 = %s\n", string2);
	printf("string3 = %s\n", string3);




	return (EXIT_SUCCESS);
}
