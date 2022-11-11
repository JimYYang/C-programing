#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

int checkFileFormat(char * file) {
    char * suffix = ".txt";
    size_t s1 = strlen(file);
    size_t s2 = strlen(suffix);
    return s1 >= s2 && strcmp(file + s1 - s2, suffix) == 0;
}


counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");

  char * line = NULL;
  size_t sz = 0;
  
  counts_t * c = createCounts();
  while (getline(&line, &sz, f) >= 0) {
    char * pos = strchr(line, '\n');
    *pos = '\0';
    char * val = lookupValue(kvPairs, line);
    addCount(c, val);
    /* line = NULL; */
    // if we using the memory of line, we should let line = NULL
    // if not, delete the clause
  }
  free(line);
  if (fclose(f) != 0) {
     perror("Can not close the file");
     return NULL;
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)

 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c



 //free the memory for kv

    if (argc < 2) {
        fprintf(stderr, "few arguments\n");
        return EXIT_FAILURE;
    }

    kvarray_t * kvpair = readKVs(argv[1]);

    for (int i = 2; i < argc; i ++) {
        if (!checkFileFormat(argv[i])) {
            perror("Invalid file format");
            return EXIT_FAILURE;
        }
        counts_t * c = countFile(argv[i], kvpair);
        char * out = computeOutputFileName(argv[i]);
        FILE * ans = fopen(out, "w");
        printCounts(c, ans);
        if (fclose(ans) != 0) {
            perror("Can not close file");
            return EXIT_FAILURE;
        }
        free(out);
        freeCounts(c);
    }
    freeKVs(kvpair);


    return EXIT_SUCCESS;
}

