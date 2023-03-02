#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "malloc.h"

/* FIX ME */
#define ROUND_UP(X) ((X) + ALIGN - ((X) % ALIGN))

size_t pagesize;
static size_t pagedbytes = 0;

/**
 * naive_malloc - Creates an allocation in the heap and returns an address
 * @size: The size requested by the calling function to allocate
 * Return: The allocated address, NULL if failed
*/

void *naive_malloc(size_t size)
{
	static char isSetUp = FALSE;
	static void *heapstart = NULL;
	void *retptr;
	sblock_t *this_block;

	if (!isSetUp)
	{
		isSetUp = TRUE;
		pagesize = (size_t) sysconf(_SC_PAGESIZE);
		pagedbytes = pagesize;
		heapstart = sbrk(0);
		sbrk(pagesize);
		this_block = heapstart;
		this_block->inuse = ISFREE;
		this_block->allocsize = pagesize;
	}
	if (size == 0)
		return (NULL);

	retptr = add_alloc(heapstart, ROUND_UP(size));
	return (retptr);
}

/**
 * add_alloc - Adds the allocation to the program data section that was extended
 * @heapstart: This is where the heap section starts
 * @size_to_alloc: the aligned size of the malloc requested by the calling function
 * Return: The allocated address, NULL if failed
*/
void *add_alloc(void *heapstart, size_t size_to_alloc)
{
	size_t traversedbytes = 0;
	sblock_t *this_block;
	sblock_t *next_block;
	size_t temp_size;
	static int i = 0;
	int j = 0;

	while (traversedbytes < pagedbytes)
	{
		j++;
		this_block = (sblock_t *) ((char *) heapstart + traversedbytes);
		while (traversedbytes + size_to_alloc + 8 > pagedbytes)
		{
			if (traversedbytes + this_block->allocsize == pagedbytes)
			{
				if (this_block->inuse == ISFREE)
					this_block->allocsize += pagesize;
				else
				{
					if (sbrk(pagesize) == (void *) -1)
						return (NULL);
					temp_size = pagedbytes;
					pagedbytes += pagesize;
					next_block = (sblock_t *) ((char *) heapstart + pagedbytes);
					next_block->inuse = ISFREE;
					next_block->allocsize = pagesize;
				}
			}
			pagedbytes += pagesize;
			if (sbrk(pagesize) == (void *) -1)
				return (NULL);
		}
		if (this_block->inuse == ISFREE && this_block->allocsize >= size_to_alloc + 16)
		{
			temp_size = this_block->allocsize;
			this_block->inuse = ISALLOC;
			this_block->allocsize = size_to_alloc + 8;
			next_block = (sblock_t *)((char *) this_block + this_block->allocsize);
			next_block->inuse = ISFREE;
			next_block->allocsize = temp_size - (size_to_alloc + 8);
			i++;
			return (this_block + 1);
		}
		traversedbytes += this_block->allocsize;
	}
	return (NULL);
}
