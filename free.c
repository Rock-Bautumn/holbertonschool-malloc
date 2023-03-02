#include "malloc.h"

#define FALSE 0
#define TRUE 1
#define ISFREE 0
#define ISALLOC 1
#define ALIGN 8


/**
 * _free - Frees a block previously allocated using _malloc()
 * @ptr: The address of the allocated memory to free
 * Return: EXIT_SUCCESS if success, EXIT_FAILURE if failed
*/
int _free(void *ptr)
{
	block_t *this_block;
	
	if (ptr)
		this_block = (block_t *) ((char *) ptr - sizeof(block_t));
	else
		return (EXIT_FAILURE);

	this_block->inuse = ISFREE;

	return (EXIT_SUCCESS);
}
