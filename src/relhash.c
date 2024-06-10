/*-------------------------------------------------------------------------
 * relhash.c
 * 
 * hash for relation info
 * 
 * IDENTIFICATION
 *      relhash.c
 *-------------------------------------------------------------------------
 */

#include <relhash.h>
#include <ereport.h>

/*
 * Hash function 
 */
static uint32 
RHTHashFunc(Oid oid, uint32 base)
{
    return oid % base;
}

/*
 * Get empty element number to insert 
 *
 * If hashtable is overflow, return 0, 
 * else return 1 
 */
static bool 
RHTGetEmptyElN(RelHashTable rht, Oid oid, uint32 *result)
{
    uint32 hashed_val = 0;
    bool hash_el_found = false;

    hashed_val = RHTHashFunc(oid, rht->n_els);

    for (int i = 0; i < rht->n_els; i++)
    {
        if (rht->hash_el_arr[hashed_val].oid != 0)
        {
            hashed_val++;
            if (hashed_val == rht->n_els)
                hashed_val = 0;
        }
        else
        {
            hash_el_found = 1;
            break;
        }
    }

    *result = hashed_val;
    return hash_el_found;
}

/*
 * Get filled element number by oid 
 * 
 * If element is not found, return 0, 
 * else return 1
 */
static bool 
RHTGetNumFilledEl(RelHashTable rht, Oid oid, uint32 *result)
{
    uint32 hashed_val = 0;
    bool hash_el_found = false;

    hashed_val = RHTHashFunc(oid, rht->n_els);

    for (int i = 0; i < rht->n_els; i++)
    {
        if (rht->hash_el_arr[hashed_val].oid == oid)
        {
            hash_el_found = 1;
            break;
        }
        else
        {
            hashed_val++;
            if (hashed_val == rht->n_els)
                hashed_val = 0;
        }
    }

    *result = hashed_val;
    return !hash_el_found;
}

/* Init relation hashtable */
RelHashTable
RHTInit(uint32 n_els)
{
    RelHashTable rht = NULL;

    if (n_els == 0)
        ereport(ERROR, "Hashtable can't contain 0 elements");

    rht = (RelHashTableData *) myalloc(sizeof(RelHashTableData), true);

    rht->hash_el_arr = (RelHashEl *) myalloc(n_els * sizeof(RelHashEl), true);

    rht->n_els = n_els;

    return rht; 
}

/* Drop relation hashtable */
void
RHTDrop(RelHashTable rht)
{
    if (rht == NULL)
        return;

    for(int i = 0; i < rht->n_els; i++)
    {
        if (rht->hash_el_arr[i].oid != 0)
            free(&rht->hash_el_arr[i]);
    }

    free(rht->hash_el_arr);
    free(rht);
}

/*
 * Init relation in relation hashtable
 * 
 * returns number of target element 
 */
uint32
RHTInitRel(RelHashTable rht, Oid oid)
{
    uint32 n_empty_el = 0;
    bool hash_not_overflow = false;
    
    hash_not_overflow = RHTGetEmptyElN(rht, oid, &n_empty_el);
    if (!hash_not_overflow)
        ereport(ERROR, "Hashtable overflow");

    rht->hash_el_arr[n_empty_el].oid = oid;

    rht->hash_el_arr[n_empty_el].rel_info = myalloc(sizeof(RelInfo), true);

    return n_empty_el;
}

/* 
 * Add a value to the number of pages and segments of a specific 
 * relation fork
 * 
 * If relation info don't stored in Relation hashtable,
 * we will use RHTInitRel() function.
 */
void
RHTAddPagesAndSegs(RelHashTable rht, Oid oid, int32 fork_type, 
                   int32 n_segs, int32 n_pages)
{
    uint32 n_el = 0;  
    bool hash_el_not_found = false;

    hash_el_not_found = RHTGetNumFilledEl(rht, oid, &n_el); 

    if (hash_el_not_found) 
        n_el = RHTInitRel(rht, oid);

    switch (fork_type)
    {
        case FT_main:
            // processing overflow types
             
            rht->hash_el_arr[n_el].rel_info->n_main_segs += n_segs;
            rht->hash_el_arr[n_el].rel_info->n_main_pages += n_pages;
            break;
        case FT_init:
            rht->hash_el_arr[n_el].rel_info->n_init_segs += n_segs;
            rht->hash_el_arr[n_el].rel_info->n_init_pages += n_pages;
            break;
        case FT_fsm:
            rht->hash_el_arr[n_el].rel_info->n_fsm_segs += n_segs;
            rht->hash_el_arr[n_el].rel_info->n_fsm_pages += n_pages;
            break;
        case FT_vm:
            rht->hash_el_arr[n_el].rel_info->n_vm_segs += n_segs;
            rht->hash_el_arr[n_el].rel_info->n_vm_pages += n_pages;
            break;
        default:
            ereport(ERROR, "non-existent fork");
    }
}

/*
 * Get Relation info by oid
 *
 * If Relinfo not found, return 0,
 * else return 1
 */
bool
RHTGetRelInfo(RelHashTable rht, Oid oid, RelInfo *rel_info)
{
    uint32 n_el = 0;
    bool el_not_found = false;

    el_not_found = RHTGetNumFilledEl(rht, oid, &n_el);
    if (el_not_found)
        return 0;

    rel_info = rht->hash_el_arr[n_el].rel_info;

    return 1;
}