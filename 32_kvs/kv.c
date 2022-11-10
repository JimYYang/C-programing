#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * findKV(char * line) {
    char * equal_pos = strchr(line, '=');
    *equal_pos = '\0';
    ++ equal_pos;
    char * newline = strchr(equal_pos, '\n');
    *newline = '\0';
    kvpair_t * kv = malloc(sizeof(*kv));
    kv -> key = line;
    kv -> value = equal_pos;
    return kv;
}


kvarray_t * readKVs(const char * fname) {
  //WRITE ME

    FILE * f = fopen(fname, "r");
    kvarray_t * arr = malloc(sizeof(*arr));
    arr -> kvpairs = NULL;
    arr -> numOfkvpairs = 0;
    int cnt = 0;

    char * line = NULL;
    size_t sz = 0;
    kvpair_t ** pairs = NULL;
    while((getline(&line, &sz, f)) >= 0) {
        pairs = realloc(pairs, (cnt + 1) * sizeof (kvpair_t *));
        pairs[cnt ++] = findKV(line);
        line = NULL;
    }
    free(line); 
    arr -> kvpairs = pairs;
    arr -> numOfkvpairs = cnt;
    if (fclose(f) != 0) {
        perror("Failed to close the input file");
        return NULL;
    }
    return arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME

    /* kvpair_t ** pair = pairs -> kvpairs; */
    /* int n = pairs -> numOfkvpairs; */

    /* for (int i = 0; i < n; i ++) { */
    /*     kvpair_t * cur = pair[i]; */
    /*     free(cur -> key); */
    /*     free(cur -> value); */
    /*     free(cur); */
    /* } */
    /* free(pair); */ 
    /* free(pairs); */

    for (int i = 0; i < pairs -> numOfkvpairs; i ++) {
        free(pairs -> kvpairs[i] -> key);
        // because k v using the same sequential memory
        /* free(pairs -> kvpairs[i] -> value); */
        free(pairs -> kvpairs[i]);
    }
    free(pairs -> kvpairs);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME

    kvpair_t ** pair = pairs -> kvpairs;
    int n = pairs -> numOfkvpairs;

    for (int i = 0; i < n; i ++) {
        kvpair_t * cur = pair[i];
        printf("key = \'%s\' value = \'%s\'\n", cur -> key, cur -> value);
    }
    
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

    kvpair_t ** pair = pairs -> kvpairs;
    int n = pairs -> numOfkvpairs;

    for (int i = 0; i < n; i ++) {
        kvpair_t * cur = pair[i];
        if (!strcmp(cur -> key, key)) {
            return cur -> value;
        }
    }
    return NULL;
}

