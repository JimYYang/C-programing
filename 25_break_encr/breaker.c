#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void decrypt(FILE * f, int * tot, int arr[]) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            tot ++;
            c = tolower(c);
            arr[c - 'a'] ++;
        }
    }
}




int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: encrypt key inputFileName\n");
        return EXIT_FAILURE;
    }
    
    FILE * f = fopen(argv[1], "r");

    if (f == NULL) {
        perror("Could not open file!");
        return EXIT_FAILURE;
    }
    
    int total = 0;
    int cnt[26] = {0};
    decrypt(f, &total, cnt);
    if (total == 0) {
	return EXIT_FAILURE;
    }
    char ch = 'a';
    double per = 0;
    for (size_t i = 0; i < 26; i ++ ) {
        if (cnt[i]) {
            per = (double)cnt[i] / total;
            if (fabs(per - 0.13) < 1e-6){
                ch = 'a' + i;
            }
        }
    }
    
    int res = (ch - 'e' + 26) % 26;
    printf("%d\n", res);

    return 0;
}

