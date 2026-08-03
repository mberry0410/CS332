#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <sys/stat.h> //will use a struct stat pointer so compile knows what it is
// 


// Function pointer type 
typedef int MYFUNC(const char *pathname,
                   const struct stat *statbuf,
                   int type,
                   int depth);

// the recursive directory traversal function 
int traverse(char *pathname,
             MYFUNC *func,
             int depth);

#endif
