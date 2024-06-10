/*------------------------------------------------------------------------- 
 *
 * ereport.h
 * 
 * error reporting
 * 
 * IDENTIFICATION 
 * 
 *       
 *------------------------------------------------------------------------- 
 */

#ifndef EREPORT_H
#define EREPORT_H

#include <c.h>

enum 
{
    DEBUG,
    LOG,
    ERROR
} ErrorLevelCode;

const char *
GetCurTimeDateAsStr(void);

const char *
GetELevelName(int elevel);

void
ELevelProcessing(int elevel);

#define ereport(elevel, ...)                                \
    do {                                                    \
        fprintf(stderr, "%s %s: ", GetCurTimeDateAsStr(),   \
                          GetELevelName(elevel));           \
        fprintf(stderr, __VA_ARGS__);                       \
        fputc('\n', stderr);                                \
        ELevelProcessing(elevel);                           \
    } while(0)

#endif  /* EREPORT_H */