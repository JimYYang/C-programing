#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
   char * OutputName = NULL;
   size_t n1 = strlen(inputName);
   OutputName = malloc((n1 + 8) * sizeof (*OutputName));
   strcpy(OutputName, inputName);
   strcat(OutputName, ".counts");
   return OutputName;
}

