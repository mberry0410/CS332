#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "traverse.h"
#include "display.h"

Options options;

/*
Name: 
BlazerID: 
Project #: HW2

To compile:
    make

To run:
    ./search
    ./search directory
    ./search -S
    ./search -s 1024
    ./search -f jpg 1
*/


int main(int argc, char *argv[])
{
    char *startDir = ".";  // Default is the current directory
    int opt;

    // Initialize options 
    options.showInfo = 0;
    options.useSize = 0;
    options.usePattern = 0;

    // Process command-line options 
    while ((opt = getopt(argc, argv, "Ss:f:")) != -1)
    {
        switch (opt)
        {
            case 'S':
                options.showInfo = 1;
                break;

            case 's':
                options.useSize = 1;
                options.maxSize = atol(optarg);
                break;

            case 'f':
                options.usePattern = 1;
                strcpy(options.pattern, optarg);

                if (optind < argc)
                {
                    options.maxDepth = atoi(argv[optind]);
                    optind++;
                }
                else
                {
                    fprintf(stderr, "Error: -f requires a depth.\n");
                    return 1;
                }
                break;

            default:
                fprintf(stderr, "Usage: ./search [-S] [-s size] [-f pattern depth] [directory]\n");
                return 1;
        }
    }

    // The remaining argument is the starting directory 
    if (optind < argc)
        startDir = argv[optind];

    // Begin directory traversal 
    traverse(startDir, processFile, 0);

    return 0;
}