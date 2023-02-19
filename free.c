#include "malloc.h"

#define FALSE 0
#define TRUE 1
#define ISFREE 0
#define ISALLOC 1
#define ALIGN 8



int _free(void *ptr)
{
	block_t *this_block = (block_t *) ((char *) ptr - sizeof(block_t));

	this_block->inuse = ISFREE;

	return (EXIT_SUCCESS);
}
