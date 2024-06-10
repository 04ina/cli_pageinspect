/*------------------------------------------------------------------------- 
 *
 * c.h
 * 
 * Extension of the C language and glibc
 * 
 * IDENTIFICATION 
 *      src/include/c.h
 *       
 *------------------------------------------------------------------------- 
 */

#include "include/c.h"

/*
 * advanced malloc
 */
void *
myalloc(size_t size, bool init_memory)
{
    Pointer pt = NULL;
    pt = malloc(size);
    if (pt == NULL) 
        ereport(ERROR, "Fatal: failed to allocate memory");

    if (init_memory)
        memset(pt, '0x00', size); 

    return pt;
}




