#ifndef _MALLOC_
#define _MALLOC_

#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ISFREE 0
#define ISALLOC 1
#define ALIGN 8

void *_malloc(size_t size);
void *add_alloc(void *heapstart, size_t size_to_alloc);
int _free(void *addr);


typedef struct block_header
{
    size_t inuse;
    size_t allocsize;
} block_t;

typedef struct sblock_header
{
    unsigned int inuse;
    unsigned int allocsize;
} sblock_t;


#endif /* _MYMALLOC_ */
