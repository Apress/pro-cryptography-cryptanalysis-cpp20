#include <stdio.h>

int main(void) 
{
    int alphabet_counting['z' - 'a' + 1]['z' - 'a' + 1] = {{ 0 }};
    int character0 = EOF, character1;
    FILE *fileBigramSampleText = fopen("bigram.txt", "r");

    if (fileBigramSampleText != NULL) 
	{
        while ((character1 = getc(fileBigramSampleText)) != EOF) 
		{
            if (character1 >= 'a' && character1 <= 'z' && character0 >= 'a' && character0 <= 'z') 
			{
                alphabet_counting[character0 - 'a'][character1 - 'a']++;
            }
            character0 = character1;
        }
        fclose(fileBigramSampleText);
        for (character0 = 'a'; character0 <= 'z'; character0++) 
		{
            for (character1 = 'a'; character1 <= 'z'; character1++) 
			{
                int number = alphabet_counting[character0 - 'a'][character1 - 'a'];
                if (number) 
				{
                    printf("%c%c: %d\n", character0, character1, number);
                }
            }
        }
    }
    return 0;
}