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

#include "ereport.h"
#include <time.h>

static const char *
GetELevelName(int elevel);

static void
ELevelProcessing(int elevel);

static const char *
GetCurTimeDateAsStr(void);

const char *
GetELevelName(int elevel)
{
    const char *buf;

    switch(elevel)
    {
        case DEBUG:
            buf = "DEBUF";
            break; 
        case LOG:
            buf = "LOG";
            break; 
        case ERROR:
            buf = "ERROR";
            break; 
    }

    return buf;
}

void
ELevelProcessing(int elevel) 
{
    if (elevel >= ERROR)
    {
        abort();
    }    
}

const char *
GetCurTimeDateAsStr(void)
{
    time_t      rawtime;
    struct tm   *timeinfo;
    char  *result_str;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    result_str = asctime(timeinfo);
    result_str[strlen(result_str) - 1] = '\0';

    return result_str; 
}