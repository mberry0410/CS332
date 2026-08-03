#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include "display.h"
#include "traverse.h"

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4
#define FTW_SL  5

// Name:
// ID: 


int traverse(char *pathname, MYFUNC *func, int depth)
{
    struct stat statbuf;
    DIR *dp;
    struct dirent *dirp;
    char newpath[PATH_MAX];

    /* Gets information about the file */
    if (lstat(pathname, &statbuf) < 0)
    {
        return func(pathname, &statbuf, FTW_NS, depth);
    }

    /* Handles regular files and symbolic links */
    if (!S_ISDIR(statbuf.st_mode))
    {
        if (S_ISLNK(statbuf.st_mode))
            return func(pathname, &statbuf, FTW_SL, depth);
        else
            return func(pathname, &statbuf, FTW_F, depth);
    }

    /* Process the directory itself */
    func(pathname, &statbuf, FTW_D, depth);

    /* Opens the directory */
    dp = opendir(pathname);

    if (dp == NULL)
    {
        return func(pathname, &statbuf, FTW_DNR, depth);
    }

    /* Reads every entry in the directory */
    while ((dirp = readdir(dp)) != NULL)
    {
        /* Skip "." and ".." */
        if (strcmp(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0)
        {
            continue;
        }

        /* Builds the new pathname */
        snprintf(newpath,
                 sizeof(newpath),
                 "%s/%s",
                 pathname,
                 dirp->d_name);

        /* Recursive call */
        traverse(newpath, func, depth + 1);
    }

    closedir(dp);

    return 0;
}