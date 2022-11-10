#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME

    counts_t * count = malloc(sizeof(*count));
    count -> arr = NULL;
    count -> n = 0;
    count -> arr = malloc (sizeof(one_count_t *));   
    count -> n_unknow = 0;
    return count;
    
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME

    if (name == NULL) {
        ++ c -> n_unknow;
        return ;
    }
    
    for (int i = 0; i < c -> n; i ++) {
        if (!strcmp(c -> arr[i] -> value, name)) {
            ++ c -> arr[i] -> n;
            return;
        }
    }

    c -> arr = realloc(c -> arr, ((c -> n) + 1) * sizeof (one_count_t *));
    /* c -> arr[c -> n] -> value = name; */
    // can not let value = name (char *, const char *);
    c -> arr[c -> n] = NULL;

    // must ask for memory first
    // otherwise the value don't exist
    c -> arr[c -> n] = malloc(sizeof(one_count_t));
    c -> arr[c -> n] -> value = NULL;
    c -> arr[c -> n] -> value = malloc(strlen(name) + 1);
    strcpy(c -> arr[c -> n] -> value, name);
    c -> arr[c -> n] -> n  = 1; // not initialized
    ++ c -> n;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
    for (int i = 0; i < c -> n; i ++) {
        fprintf(outFile, "%s: %d\n", c -> arr[i] -> value, c -> arr[i] -> n);
    }
    
    if (c -> n_unknow)
        printf("<unknown>: %d\n", c -> n_unknow);
}

void freeCounts(counts_t * c) {
  //WRITE ME
    for (int i = 0; i < c -> n; i ++) {
        free(c -> arr[i] -> value);
        free(c -> arr[i]);
    }
    // be clearly that which pointer be allocated the memory
    free(c -> arr);
    free(c);
}

