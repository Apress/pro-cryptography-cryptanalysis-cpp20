#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sBox_content[16] = {9, 11, 12, 4, 10, 1, 2, 6, 13, 7, 3, 8, 15, 14, 0, 5};
int sBox_content_revision[16] = {14, 5, 6, 10, 3, 15, 7, 9, 11, 0, 4, 1, 2, 8, 13, 12};
int approximation_array[16][16];
int known_plaintext[500];
int known_ciphertext[500];
int numbers_known = 0;

int using_mask(int inputValue, int mask_value)	
{
    int value = inputValue & mask_value;
    int total = 0;
    
    while(value > 0)
    {
        int temporary = value % 2;    
        value /= 2;
        
        if (temporary == 1)
		{
            total = total ^ 1;
		}
    } 
    return total;   
}

void looking_for_approximation()		
{
    int a, b, c;
    
	//** the output of mask value
    for(a = 1; a < 16; a++)
    {
		//** the input of mask value
		for(b = 1; b < 16; b++)
		{
			//** input
            for(c = 0; c < 16; c++)
			{
                if (using_mask(c, b) == using_mask(sBox_content[c], a))
				{
                    approximation_array[b][a]++;
				}
			}
		}
	}
}

void display_approximation()
{
    printf("Linear Approximations Values: \n");
    
	int a, b, c;		
    for(a = 1; a < 16; a++)
        for(b = 1; b < 16; b++)
            if (approximation_array[a][b] == 14)
                printf("  %i : %i {--} %i\n", approximation_array[a][b], a, b);    
 
    printf("\n");
}

int round_function(int inputValue, int substitution_key)	
{
    return sBox_content[inputValue ^ substitution_key]; 
}

void filling_known_numbers()	
{
    int substitution_key_1 = rand() % 16;
    int substitution_key_2 = rand() % 16;
    
    printf("Generating data:  Key_1 = %i, Key_2 = %i\n", substitution_key_1, substitution_key_2);
    
    int total = 0;

    int c;
    for(c = 0; c < numbers_known; c++)
    {
        known_plaintext[c] = rand() % 16;
        known_ciphertext[c] = round_function(round_function(known_plaintext[c], substitution_key_1), substitution_key_2); 
    }    
    
    printf("Generating Data:  We have %i known pairs generated\n\n", numbers_known);
        
}

void keys_testing(int key_1, int key_2)		//testKeys
{
    int c;
    for(c = 0; c < numbers_known; c++)
	{
        if (round_function(round_function(known_plaintext[c], key_1), key_2) != known_ciphertext[c])    
		{
            break;
		}
	}
            
    printf("# ");
}

int main()
{
    printf("Linear Cryptanalysis\n\n");
    
    srand(time(NULL));
    
    looking_for_approximation();
    display_approximation();
    
    int input_approximation = 11;
    int output_approximation = 11;
    
	//** how many numbers we known
    numbers_known = 16;						
    filling_known_numbers();
    
    int cryptographic_key_score[16];
    int reaching_threshold = 0;					//sofar1
    
    printf("Proceeding with Linear Attack");
	printf("\tLinear Approximation = %i -> %i\n", input_approximation, output_approximation);
    printf("\n\n");
   
    int b, h;
    for(b = 0; b < 16; b++)
    {
        cryptographic_key_score[b] = 0;
        for(h = 0; h < numbers_known; h++)
        {
            reaching_threshold++;
            int middle_round = round_function(known_plaintext[h], b);         //Find Xi by guessing at K1
            
            if ((using_mask(middle_round, input_approximation) == using_mask(known_ciphertext[h], output_approximation)))
                cryptographic_key_score[b]++;
            else
                cryptographic_key_score[b]--;
                
        }            
    }

    int maximum_score_value = 0;
    
    for(b = 0; b < 16; b++)
    {
        int score_value = cryptographic_key_score[b] * cryptographic_key_score[b];
        if (score_value > maximum_score_value) maximum_score_value = score_value;
    }
    
    int good_cryptographic_keys[16];
    
    for(h = 0; h < 16; h++)
        good_cryptographic_keys[h] = -1;
    
    h = 0;
    
	printf("Linear Attack:\n");
    for(b = 0; b < 16; b++)
	{
        if ((cryptographic_key_score[b] * cryptographic_key_score[b]) == maximum_score_value)
        {
            good_cryptographic_keys[h] = b;         
			printf("\tPotential Value Candidate for Cryptography Key 1 = %i\n", good_cryptographic_keys[h]);
            h++;
        }
	}
    
    int guessing_cryptographic_key_1;
	int guessing_cryptographic_key_2;
    
    for(h = 0; h < 16; h++)    
    {
        if (good_cryptographic_keys[h] != -1)
        {
			int cryptography_key_test_1 = round_function(known_plaintext[0], good_cryptographic_keys[h]) ^ sBox_content_revision[known_ciphertext[0]];

			int tested = 0;
			int e;
			int bad = 0;
			for(e = 0;e < numbers_known; e++)
			{
				reaching_threshold += 2;
				int testOut = round_function(round_function(known_plaintext[e], good_cryptographic_keys[h]), cryptography_key_test_1);
				if (testOut != known_ciphertext[e])
					bad = 1;
			}
			if (bad == 0) 
			{
				printf("\tFound Keys! K1 = %i, K2 = %i\n", good_cryptographic_keys[h], cryptography_key_test_1);
				guessing_cryptographic_key_1 = good_cryptographic_keys[h];
				guessing_cryptographic_key_2 = cryptography_key_test_1;
				printf("\tComputations Until Key Found = %i\n", reaching_threshold);
				
			} 
        }    
    }
    
    printf("\tThe total value of computations = %i\n\n", reaching_threshold);    
    reaching_threshold = 0;
    
	printf("Brute Force Attack\n");
    for(h = 0; h < 16; h++)    
    {
		for(b = 0; b < 16; b++)
		{		
			int e;
			int bad = 0;
			for(e = 0;e < numbers_known; e++)
			{
				reaching_threshold += 2;
				int testOut = round_function(round_function(known_plaintext[e], h), b);
				if (testOut != known_ciphertext[e])
					bad = 1;
			}
			if (bad == 0) 
			{
				printf("\tCryptographic Keys Found with Success! K1 = %i, K2 = %i\n", h, b);
				printf("\tThe number of computations computed until the cryptography key(s) were found = %i\n", reaching_threshold);
			}
		}       
    }

    printf("\tComputations Total = %i\n", reaching_threshold);
}