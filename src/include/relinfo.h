/*
 * relinfo.h
 * 
 * Data types for storing info about relations 
 * 
 * IDENTIFICATION
 *      include/relinfo.h
 */

#ifndef RELINFO_H
#define RELINFO_H

#include "c.h"

/* Relation object id */
typedef uint32 Oid;

/* 
 * Structure for relations stores 
 * number of certain pages and segments
 */
typedef struct RelInfo {
    /* Segments number of certain relation fork */
    uint32 n_main_segs;
    uint32 n_init_segs;
    uint32 n_fsm_segs;
    uint32 n_vm_segs;

    /* Pages number of certain relation fork */
    uint32 n_main_pages;
    uint32 n_init_pages;
    uint32 n_fsm_pages;
    uint32 n_vm_pages;
} RelInfo;

#endif  /* RELINFO_H */