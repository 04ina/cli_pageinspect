/*-------------------------------------------------------------------------
 * relhash.h
 * 
 * hash for relations   
 * 
 * IDENTIFICATION
 *      include/relhash.h
 *-------------------------------------------------------------------------
 */
#ifndef RELHASH_H 
#define RELHASH_H 

#include "relinfo.h"

/*
 * Relation hashtable element
 */
typedef struct RelHashEl
{
    RelInfo *rel_info;
    Oid     oid;
} RelHashEl;

/*
 * Relation hashtable
 */
typedef struct RelHashTableData
{
    /* RelHashEl Array */
    RelHashEl *hash_el_arr;

    /* Number of hash elements*/ 
    uint32    n_els;
} RelHashTableData;

typedef RelHashTableData *RelHashTable;

/* 
 * Types of forks
 */
typedef enum {
    FT_main,
    FT_init,
    FT_fsm,
    FT_vm
} ForkTypes; 


RelHashTable
RHTInit(uint32 n_el);

void
RHTDrop(RelHashTable rht);

uint32
RHTInitRel(RelHashTable rht, Oid oid);

void
RHTAddPagesAndSegs(RelHashTable rht, Oid oid, int32 fork_type, 
                   int32 n_segs, int32 n_pages);

bool
RHTGetRelInfo(RelHashTable rht, Oid oid, RelInfo *rel_info);

#endif  /* RELHASH_H */