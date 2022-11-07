#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

void rotate(char matrix[10][10])
{
    int N = 10;
    for (int layer = 0; layer < N / 2; ++layer)
    {
        int maxValue = N-layer-1;
        int minValue = layer;
        for(int i = minValue; i < maxValue; ++i)
        {
        int offset = i - minValue;
        //temporary top value
        char top = matrix[minValue][minValue + offset];
        //top = left
        matrix[minValue][minValue+offset] = matrix[maxValue - offset][minValue];
        //left = bottom
        matrix[maxValue-offset][minValue] = matrix[maxValue][maxValue-offset];
        //bottom = right
        matrix[maxValue][maxValue - offset] = matrix[minValue + offset][maxValue];
        //right = top
        matrix[minValue + offset][maxValue] = top;

        }
	}
}

int checkInputFormat(char * a)
{
    char * suffix = ".txt";
    size_t slen = strlen(a);
    size_t suffix_len = strlen(suffix);
    return suffix_len <= slen && !strcmp(a + slen - suffix_len, suffix);
}
int checkFileContents(FILE * f)
{
    int c;
    int rows = 0;
    int chars = 0;
    c = fgetc(f);
    while(c != EOF)
    {
        //if(c == 0xFF) continue;
        if(c != '\n' && isprint(c)) ++chars;
        if(c == '\n') ++rows;
        c = fgetc(f);
    }
    if(rows == 10 && chars ==100) return 1;
    return 0;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        perror("Wrong input");;
        return EXIT_FAILURE;
    }
    if(!checkInputFormat(argv[1]))
    {
        perror("Wrong file format");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if(f == 0)
    {
        perror( "Invalid file");
        return EXIT_FAILURE;
    }
    if(!checkFileContents(f))
    {
        perror("File contents invalid");
        return EXIT_FAILURE;
    }
    rewind(f);
    char arr[10][10];
    int c;
    for(int i = 0 ; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            c = fgetc(f);
            if(c == '\n') c = fgetc(f);
            arr[i][j] = c;
        }
        c = fgetc(f);
    }
    rotate(arr);
    for(int a = 0; a < 10; ++a)
    {
        for(int b = 0; b < 10; ++b)
        {
            printf("%c", arr[a][b]);
        }
        printf("\n");
    }
    if(fclose(f) != 0)
    {
        perror("File did not close");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

