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
#ifndef C_H
#define C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include <errno.h>

/*
 * Instead of *void
 */
typedef char *Pointer;

/*
 * Types for signed intN 
 */
typedef signed char             int8;
typedef signed short            int16;		
typedef signed int              int32;	
typedef signed long long int    int64;

/*
 * Types for unsigned intN 
 */
typedef unsigned char           uint8;
typedef unsigned short          uint16;	
typedef unsigned int            uint32;
typedef unsigned long long int  uint64;

/*
 * Types for float 
 */
typedef float float32;
typedef double float64;

/*
 * String type
 */
typedef char *String;

void *
myalloc(size_t size, bool init_memory);

#endif  /* C_H */