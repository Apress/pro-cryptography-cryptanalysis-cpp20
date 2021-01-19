#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//** variables
int theSBox[16] = {3, 14, 1, 10, 4, 9, 5, 6, 8, 11, 15, 2, 13, 12, 0, 7};
//int theSBox[16] = {14, 2, 11, 0, 4, 6, 7, 15, 8, 5, 3, 9, 13, 12, 1, 10};
int characters[16][16];
int known_plaintext_0[10000];					
int known_plaintext_1[10000];					
int known_ciphertext_0[10000];					
int known_ciphertext_1[10000];
int good_plaintext_0, good_plaintext_1, good_ciphertext_0, good_ciphertext_1;
int pairs_of_numbers;	
int characters_dataSet_0[16];						
int characters_data_max = 0;							


int round_function(int integer_input, int cryptoKey)		
{
    return theSBox[cryptoKey ^ integer_input];    
}

int encryption(int integer_input, int key_0, int key_1)
{
    int x_value_0 = round_function(integer_input, key_0);
    return x_value_0 ^ key_1;        
}

void find_differences()
{
    printf("\nXOR Differential Structure:\n");
    
    int a, b, c, f;		//c, d, e, f
    
    for(a = 0; a < 16; a++)
	{
        for(b = 0; b < 16; b++)
		{
            characters[a ^ b][theSBox[a] ^ theSBox[b]]++;        
		}
	}
 
    for(a = 0; a < 16; a++)
    {
        for(b = 0; b < 16; b++)
            printf("  %x ", characters[a][b]);
        printf("\n");
    }
    
    printf("\nShowing the most important differences:\n");
    
    for(a = 0; a < 16; a++)
	{
        for(b = 0; b < 16; b++)
		{
            if (characters[a][b] == 6)            
			{
				printf("  6/16:   %i {--} %i\n", a, b);  
			}
		}
	}
}

void generate_characters_data(int input_differences, int output_differences)
{
            printf("\nIntermediate values generated using the differentials(%i --> %i):\n", input_differences, output_differences);
			
            characters_data_max = 0;
            int f;
            for(f = 0; f < 16; f++)
            {
                int computations = f ^ input_differences;
                
                if ((theSBox[f] ^ theSBox[computations]) == output_differences)         
                {
					printf("  The possibility:   %i + %i {--} %i + %i\n", f, computations, theSBox[f], theSBox[computations]);
                    characters_dataSet_0[characters_data_max] = f;
                    characters_data_max++;
                }
            }    
}

void generate_pairs(int input_differences)
{
    printf("\nKnown pairs %i generated. The pairs are based on the differentials served as input of %i.\n", pairs_of_numbers, input_differences);
    
	//** generate substitution keys
    int real_key_0 = rand() % 16;                                                      
    int real_key_1 = rand() % 16;                                                       
    
    printf("  Real Key 0 = %i\n", real_key_0);
    printf("  Real Key 1 = %i\n", real_key_1);
        
    int c;
	
	//** using XOR, pairs for plaintexts and ciphertexts are generated
    for(c = 0; c < pairs_of_numbers; c++)                                               
    {
        known_plaintext_0[c] = rand() % 16;
        known_plaintext_1[c] = known_plaintext_0[c] ^ input_differences;
        known_ciphertext_0[c] = encryption(known_plaintext_0[c], real_key_0, real_key_1);
        known_ciphertext_1[c] = encryption(known_plaintext_1[c], real_key_0, real_key_1);
    }  
}

void identifying_good_pair(int output_differences)
{
    printf("\nLooking for good pair:\n");
    int c;
	
	//** test if the pair of ciphertexts meet the characteristics
    for(c = 0; c < pairs_of_numbers; c++)
	{
        if ((known_ciphertext_0[c] ^ known_ciphertext_1[c]) == output_differences)                               
        {   
            good_ciphertext_0 = known_ciphertext_0[c];
            good_ciphertext_1 = known_ciphertext_1[c];
            good_plaintext_0 = known_plaintext_0[c];
            good_plaintext_1 = known_plaintext_1[c];   
			printf("  A good pair has been found: (P0 = %i, P1 = %i) {--} (C0 = %i, C1 = %i)\n", good_plaintext_0, good_plaintext_1, good_ciphertext_0, good_ciphertext_1);        
            return;    
        }
	}		
    printf("There was no good pair found!\n");
}

int key_testing(int key_test_0, int key_test_1)
{
    int c;
    int crap = 0;
    for(c = 0; c < pairs_of_numbers; c++)
    {
        if ((encryption(known_plaintext_0[c], key_test_0, key_test_1) 
			!= known_ciphertext_0[c]) || (encryption(known_plaintext_1[c], key_test_0, key_test_1) != known_ciphertext_1[c]))
        {
            crap = 1;
            break;
        }        
    }
    
    if (crap == 0)
        return 1;     
    else   
        return 0;   
}

void brute_cracking()
{
    printf("\nReducing the space of the key using brute force:\n");
    
    int f;
	
	//** based on the characteristics, we will test each of the possible value
    for(f = 0; f < characters_data_max; f++)                                             
    {
        int key_test_0 = characters_dataSet_0[f] ^ good_plaintext_0;
        int key_test_1 = theSBox[characters_dataSet_0[f]] ^ good_ciphertext_0 ;

        if (key_testing(key_test_0, key_test_1) == 1)
            printf("\n\nThe Key! (%i, %i), ", key_test_0, key_test_1);
        else
            printf("       (%i, %i), ", key_test_0, key_test_1);
    }  
}

int main()
{
	//** generate random value once the program is run
    srand(time(NULL));                                                          
    
	//** look in the s-boxes for good differences
    find_differences();                                                                
    
    //** define number of known pairs
	pairs_of_numbers = 8;                                                               
    
    //** look for inputs that meet specific characteristics
	generate_characters_data(4, 7);                                                          
    
	//** let's generate pairs of chosen-plaintext
	generate_pairs(4);
    
	//** pick a pair which meet the characteristic
	identifying_good_pair(7);
	
	//** find the key
    brute_cracking();        
}
