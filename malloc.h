#ifndef _MALLOC_
#define _MALLOC_

#include <stdlib.h>

void *_malloc(size_t size);
void *add_alloc(void *heapstart, size_t size_to_alloc);


typedef struct block_header
{
    size_t inuse;
    size_t allocsize;
} block_t;


#endif /* _MYMALLOC_ */
