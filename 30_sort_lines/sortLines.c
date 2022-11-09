#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
	const char * const * p1 = vp1;
	const char * const * p2 = vp2;
	return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
	qsort(data, count, sizeof(char *), stringOrder);
}

char ** help(FILE * f, size_t *n) {
	char ** arr = NULL;
	char * line = NULL;
	size_t sz = 0;
	while ((getline(&line, &sz, f)) > 0) {
		arr = realloc(arr, ((*n) + 1) * sizeof(*arr));
		arr[(*n)++] = line;
		line = NULL;
	}
	free(line);
	sortData(arr, *n);
	return arr;
}

int main(int argc, char ** argv) {

	if (argc == 0) {
		fprintf(stderr,"few arguments \n");
		return EXIT_FAILURE;
	}

	else if(argc == 1) {
		size_t total = 0;
		char ** arr = help(stdin, &total);
		for (size_t j = 0; j < total; j ++) {
			printf("%s", arr[j]);
			free(arr[j]);
		}
		free(arr);

	}

	else {

		for (size_t i = 1; i < argc; i ++) {
			FILE * f = fopen(argv[i], "r");
			if (f == NULL) {
				perror("Could not open file");
				return EXIT_FAILURE;
			}

			size_t total = 0;
			char ** arr = help(f, &total);

			for (size_t j = 0; j < total; j ++) {
				printf("%s", arr[j]);
				free(arr[j]);
			}
			free(arr);
			if (fclose(f) != 0) {
				perror("Failed to close the input file");
				return EXIT_FAILURE;
			}
		}

	}
	return EXIT_SUCCESS;
}

