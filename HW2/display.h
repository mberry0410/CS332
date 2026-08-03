#ifndef DISPLAY_H
#define DISPLAY_H

#include <sys/types.h>
#include <sys/stat.h>
// Name: 
// ID: 


// structure to store command-line options 
typedef struct
{
    int showInfo;          // -S 

    int useSize;           // -s 
    off_t maxSize;

    int usePattern;        // -f 
    char pattern[256];
    int maxDepth;

} Options;

// Global options structure 
extern Options options;

// Callback function used during traversal 
int processFile(const char *pathname,
                const struct stat *statbuf,
                int type,
                int depth);

#endif