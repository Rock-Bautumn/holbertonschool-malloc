#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	void *p;

	p = malloc(0);
	printf("pointer = %p\n", (void *) p);

	strcpy(p, "Holberton");
	printf("string = %s\n", (char *) p);

	free(p);
	return 0;
}
