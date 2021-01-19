#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//** VARIABLES
//** the sBox structure
int sboxValue[16] = {9, 11, 12, 4, 10, 1, 2, 6, 13, 7, 3, 8, 15, 14, 0, 5};	
//** the revision sBox value structure
int revision_sbox_value[16] = {14, 5, 6, 10, 3, 15, 7, 9, 11, 0, 4, 1, 2, 8, 13, 12};
//** an approximation array 
int approximation_array_structure[16][16];		
//** the maximum score which will need to be compared with the "score" variable									
int maximum_score = 0;
//** the total value																
int total_value = 0;
//** control counters, 1 and 2																
int counter1;
int counter2;
//** generating known plaintext
int known_plaintext[500];
//** generating known ciphertext																
int known_ciphertext[500];	
//** number of generated known pairs 															
int known_numbers = 0;
//** approximation values, for input and output
int approximation_for_input = 11;																
int approximation_for_output = 11;
//** score value for the cryptography key																
int cryptographyKey_score_value[16];	
//** the threshold level. used for identitying the step until we reached for finding the cryptography keys																
int threshold_level = 0;
//** good reliable cryptography key																			
int reliable_crypto_keys[16];	
//** the values for the guessed cryptography key													
int guessing_crypto_key1, guessing_crypto_key2;		
//** testing control variable for cryptography key							
int cryptoKey1_testing;													

//** apply the mask
int applying_the_mask(int theValue, int mask_value)					
{
    int internal_value = theValue & mask_value;					
    int total_value = 0;
    
    while(internal_value > 0)
    {
        int temporary = internal_value % 2;    
        internal_value /= 2;
        
        if (temporary == 1) 
            total_value = total_value ^ 1;
    } 
    return total_value;   
}

//** detecting the approximation
void detect_the_approximation()												
{    
	int a, b, c;		

	//** parsing for the output mask. 16 represents the size of the s-Box
    for(a = 1; a < 16; a++)   
	{
		//** parsing for the input mask
        for(b = 1; b < 16; b++)                                  
		{
			//** parsing the input
            for(c = 0; c < 16; c++)                                
			{
                if (applying_the_mask(c, b) == applying_the_mask(sboxValue[c], a))
                    approximation_array_structure[b][a]++;
			}
		}
	}
}

//** show and display the approximation
void display_the_approximation()
{
    printf("Integral Values Approximations: \n");
    int a, b, c;
    for(a = 1; a < 16; a++)
	{
        for(b = 1; b < 16; b++)
		{
            if (approximation_array_structure[a][b] == 14)
                printf("  %i : %i {<-->} %i\n", approximation_array_structure[a][b], a, b);   
		}			
	}
 
    printf("\n");
}

//** round function for s
int rounding_procedure(int dataInput, int substitution_key)
{
    return sboxValue[dataInput ^ substitution_key]; 
}

//** filling the knowings possible key values
void filling_up_the_knowings()		
{

    int substitution_key_1 = rand() % 16;
    int substitution_key_2 = rand() % 16;
    
    printf("Generating Data:  Key 1 = %i, Key 2 = %i\n", substitution_key_1, substitution_key_2);    
    
	//** parse each known value and for each known plaintext and ciphertext compute the proper values
    for(counter1 = 0; counter1 < known_numbers; counter1++)
    {
        known_plaintext[counter1] = rand() % 16;
        known_ciphertext[counter1] = rounding_procedure(rounding_procedure(known_plaintext[counter1], substitution_key_1), substitution_key_2); 
    }    
    
    printf("Generating Data:  We have generated %i known pairs\n\n", known_numbers);        
}

//** verify and test the cryptography keys
void testing_the_keys(int key_1, int key_2)
{
    for(counter2 = 0; counter2 < known_numbers; counter2++)
        if (rounding_procedure(rounding_procedure(known_plaintext[counter2], key_1), key_2) != known_ciphertext[counter2])    
            break;
            
    printf("* ");
}

int main()
{
    printf("Testing Program for Integral Cryptanalysis\n\n");    
    
    srand(time(NULL));
    
    detect_the_approximation();
    display_the_approximation();    
    
    known_numbers = 16;
    filling_up_the_knowings();
    
    printf("Integral Cryptanalysis Attack -->  Based on Linear Approximation = %i {<-->} %i\n", approximation_for_input, approximation_for_output);
    
    int c, d;
    for(c = 0; c < 16; c++)
    {
        cryptographyKey_score_value[c] = 0;
        for(d = 0; d < known_numbers; d++)
        {
            threshold_level++;
            int midRound = rounding_procedure(known_plaintext[d], c);         //Find Xi by guessing at K1
            
            if ((applying_the_mask(midRound, approximation_for_input) == applying_the_mask(known_ciphertext[d], approximation_for_output)))
                cryptographyKey_score_value[c]++;
            else
                cryptographyKey_score_value[c]--;                
        }            
    }    
    
    for(c = 0; c < 16; c++)
    {
        int score = cryptographyKey_score_value[c] * cryptographyKey_score_value[c];
        if (score > maximum_score) maximum_score = score;
    }
    
    for(d = 0; d < 16; d++)
	{
        reliable_crypto_keys[d] = -1;
	}
    
    d = 0;
    
    for(c = 0; c < 16; c++)
	{
        if ((cryptographyKey_score_value[c] * cryptographyKey_score_value[c]) == maximum_score)
        {
            reliable_crypto_keys[d] = c;
            printf("Integral Cryptanalysis Attack -->  Candidate for K1 = %i\n", reliable_crypto_keys[d]);
            d++;
        }
	}
    
    for(d = 0; d < 16; d++)    
    {
        if (reliable_crypto_keys[d] != -1)
        {
                cryptoKey1_testing = rounding_procedure(known_plaintext[0], reliable_crypto_keys[d]) ^ revision_sbox_value[known_ciphertext[0]];

                int tested = 0;
                int e;
                int bad = 0;
                for(e = 0;e < known_numbers; e++)
                {
                    threshold_level += 2;
                    int testOut = rounding_procedure(rounding_procedure(known_plaintext[e], reliable_crypto_keys[d]), cryptoKey1_testing);
                    if (testOut != known_ciphertext[e])
                        bad = 1;
                }
                if (bad == 0) 
                {
                    printf("Integral Cryptanalysis Attack -->  We have found the cryptography keys! Crypto Key 1 = %i, Crypto Key 2 = %i\n", reliable_crypto_keys[d], cryptoKey1_testing);
                    guessing_crypto_key1 = reliable_crypto_keys[d];
                    guessing_crypto_key2 = cryptoKey1_testing;
                    printf("Integral Cryptanalysis Attack -->  Number of computations for reaching the cryptography key = %i\n", threshold_level);
                    
                }
 
        }    
    }
    
    printf("Integral Cryptanalysis Attack --> Computations Total = %i\n\n", threshold_level);
    
    threshold_level = 0;
    
    for(d = 0; d < 16; d++)    
    {
            for(c = 0; c < 16; c++)
            {
            
                int e;
                int bad = 0;
                for(e = 0;e < known_numbers; e++)
                {
                    threshold_level += 2;
                    int testOut = rounding_procedure(rounding_procedure(known_plaintext[e], d), c);
                    if (testOut != known_ciphertext[e])
                        bad = 1;
                }
                if (bad == 0) 
                {
                    printf("Brute Force -->  We have found the cryptography keys! Crypto Key 1 = %i, Crypto Key 2 = %i\n", d, c);
                    printf("Brute Force -->  Number of computations for reaching the cryptography key = %i\n", threshold_level);
                }
            }    
   
    }

    printf("Brute Force -->  Total computations number = %i\n", threshold_level);
    
    //while(1){}       
}