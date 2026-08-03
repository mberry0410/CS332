#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "display.h"

/* This variable was created in search.c */
extern Options options;

int processFile(const char *pathname,
                const struct stat *statbuf,
                int type,
                int depth)
{
    int i;
    const char *name;

    /* Print indentation */
    for (i = 0; i < depth; i++)
    {
        printf("\t");
    }

    /* Get just the filename */
    name = strrchr(pathname, '/');

    if (name != NULL)
    {
        name++;      /* Skip the '/' */
    }
    else
    {
        name = pathname;
    }

    /* Print the filename */
    printf("%s\n", name);

    return 0;
}
