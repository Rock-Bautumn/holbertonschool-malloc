#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "malloc.h"

#define FALSE 0
#define TRUE 1
#define ISFREE 0
#define ISALLOC 1
#define ALIGN 8


/* FIX ME */
#define ROUND_UP(X) ((X) + ALIGN - ((X) % ALIGN))

size_t pagesize;
static size_t pagedbytes = 0;

void *_malloc(size_t size)
{
	static char isSetup = FALSE;
	static void *heapstart = NULL;
	void *retptr;
	block_t *this_block;

	if (!isSetup)
	{
		isSetup = TRUE;
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

void *add_alloc(void *heapstart, size_t size_to_alloc)
{
	size_t traversedbytes = 0;
	block_t *this_block;
	block_t *next_block;
	size_t temp_size;

	while (traversedbytes < pagedbytes)
	{
		this_block = (block_t *) ((char *) heapstart + traversedbytes);
		while (traversedbytes + size_to_alloc + 16 > pagedbytes)
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
					next_block = (block_t *) ((char *) heapstart + pagedbytes);
					next_block->inuse = ISFREE;
					next_block->allocsize = pagesize;
				}
			}
			pagedbytes += pagesize;
			if (sbrk(pagesize) == (void *) -1)
				return (NULL);
		}

		if (this_block->inuse == ISFREE && this_block->allocsize >= size_to_alloc + 32)
		{
			temp_size = this_block->allocsize;
			this_block->inuse = ISALLOC;
			this_block->allocsize = size_to_alloc + 16;
			next_block = (block_t *)((char *) this_block + this_block->allocsize);
			next_block->inuse = ISFREE;
			next_block->allocsize = temp_size - (size_to_alloc + 16);

			return (this_block + 1);
		}
		traversedbytes += this_block->allocsize;
	}

	return (NULL);
}
