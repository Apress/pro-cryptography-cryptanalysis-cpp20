#include <stdio.h>
#include <string.h>

int main(void) 
{    
    // the last five bytes corresponds to ISO/IEC 8859-9
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz\xFD\xFxE7\xF6\xFC";
    const int length_of_alphabet = (sizeof(alphabet) - 1);
    int count[length_of_alphabet][length_of_alphabet];
    char *position0 = NULL;
    int character1;
    FILE *fileTextForCountingBigrams = fopen("bigram.txt", "r");

    memset(count, 0, sizeof(count));

    if (fileTextForCountingBigrams != NULL) 
	{
        while ((character1 = getc(fileTextForCountingBigrams)) != EOF) 
		{
            char *p1 = (char*)memchr(alphabet, character1, length_of_alphabet);
            if (p1 != NULL && position0 != NULL) 
			{
                count[position0 - alphabet][p1 - alphabet]++;
            }
            position0 = p1;
        }
        fclose(fileTextForCountingBigrams);
        for (size_t i = 0; i < length_of_alphabet; i++) 
		{
            for (size_t j = 0; j < length_of_alphabet; j++) 
			{
                int n = count[i][j];
                if (n > 0) 
				{
                    printf("%c%c: %d\n", alphabet[i], alphabet[j], n);
                }
            }
        }
    }
    return 0;
}