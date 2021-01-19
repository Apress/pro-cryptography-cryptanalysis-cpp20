#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

//** generate an integer that is situated between 1 to 4
int generateInteger()		
{
	//** pseudo-random generator (srand). time(NULL) represents the seed
    srand(time(NULL));
	
	//** generate a random value and store the remainder of rand() to 5
    int randomValue = rand() % 5;
	
	//** if the value is equal with 0, move to the next value of i and return that value
    if (randomValue == 0)
        randomValue++;
    return randomValue;
}

//** the function will generate randomly an integer situated between 0 and 25
int generateRandomlyInteger()		
{
	//** pseudo-random generator (srand). time(NULL) represents the seed
    srand(time(NULL));

	//** generate a random value and store the remainder of rand() with 26
    int random_key = rand() % 26;
    return random_key;
}

//** based on the length provided, the function will generate a cryptographic key
void generate_crypto_key(int length)	
{    
	//** create a string variable for cryptography key and initialize it with NULL
    string crypto_key = "";	
    
	//** variable used for cryptography key generation
    string alphabet_lower_case = "abcdefghijklmnopqrstuvwxyz";
    string alphabet_upper_case = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string special_symbols = "!@#$%&";
    string digits_and_numbers = "0123456789";

    //** local variables and their initializations
    int key_seed;
	int lowerCase_Alphabet_Count = 0;
	int upperCase_Alphabet_Count = 0;
	int digits_And_numbers_count = 0;
	int special_symbols_count = 0;

    //** the variable count will save the length of the cryptography key. initially we will set it to zero
    int countingLengthCryptoKey = 0;
    while (countingLengthCryptoKey < length) 
	{       
		//** generateInteger() function will return a number that is situated between 1 and 4.
		//** The number that is generated will be used in assignation with one of the strings that has been defined above (for example: alphabet_lower_case, alphabet_upper_case, special_symbols, and digits_and_numbers).
		//** This being said, the following correspondence will be applied: (1) for alphabet_lower_case, (2) for alphabet_upper_case, (3) for special_symbols, and (4) digits_and_numbers
        int string_type = generateInteger();        
		
		//** For the first character of the cryptography key we will put a rule in such way that it should be a letter, in such way that the string that will be selected will be an lower case alphabet or an upper case alphabet. The IF condition is quite vital as the switch is based on it and the value that string_type variable will have.
        if (countingLengthCryptoKey == 0) 
		{
            string_type = string_type % 3;
            if (string_type == 0)
               string_type++;
        }
		
        switch (string_type) 
		{
			case 1:
				//** based on the IF condition, it is necessary to check the minimum requirements of the lower case alphabet characters if they have been accomplished and fulfilled. If we are dealing with the situation in which the requirement has not been achieved we will situate ourself in the break phase.
				if ((lowerCase_Alphabet_Count == 2) 
						&& (digits_And_numbers_count == 0 
						|| upperCase_Alphabet_Count == 0 
						|| upperCase_Alphabet_Count == 1 
						|| special_symbols_count == 0))
					break;

				key_seed = generateRandomlyInteger();
				crypto_key = crypto_key + alphabet_lower_case[key_seed];
				lowerCase_Alphabet_Count++;
				countingLengthCryptoKey++;
				break;

			case 2:
				//** based on the IF condition, it is necessary to check the minimum requirements of the upper case alphabet characters if they have been accomplished and fulfilled. If we are dealing with the situation in which the requirement has not been achieved we will situate ourself in the break phase.
				if ((upperCase_Alphabet_Count == 2) 
						&& (digits_And_numbers_count == 0 
						|| lowerCase_Alphabet_Count == 0 
						|| lowerCase_Alphabet_Count == 1 
						|| special_symbols_count == 0))
					break;
				key_seed = generateRandomlyInteger();
				crypto_key = crypto_key + alphabet_upper_case[key_seed];
				upperCase_Alphabet_Count++;
				countingLengthCryptoKey++;
				break;

			case 3:				
				//** based on the IF condition, it is necessary to check the minimum requirements of the numbers if they have been accomplished and fulfilled. If we are dealing with the situation in which the requirement has not been achieved we will situate ourself in the break phase.
				if ((digits_And_numbers_count == 1) 
						&& (lowerCase_Alphabet_Count == 0 
						|| lowerCase_Alphabet_Count == 1 
						|| upperCase_Alphabet_Count == 1 
						|| upperCase_Alphabet_Count == 0 
						|| special_symbols_count == 0))
					break;

				key_seed = generateRandomlyInteger();
				key_seed = key_seed % 10;
				crypto_key = crypto_key + digits_and_numbers[key_seed];
				digits_And_numbers_count++;
				countingLengthCryptoKey++;
				break;

			case 4:
				//** based on the IF condition, it is necessary to check the minimum requirements of the special characters if they have been accomplished and fulfilled. If we are dealing with the situation in which the requirement has not been achieved we will situate ourself in the break phase.
				if ((special_symbols_count == 1) 
						&& (lowerCase_Alphabet_Count == 0 
						|| lowerCase_Alphabet_Count == 1 
						|| upperCase_Alphabet_Count == 0 
						|| upperCase_Alphabet_Count == 1 
						|| digits_And_numbers_count == 0))
					break;

				key_seed = generateRandomlyInteger();
				key_seed = key_seed % 6;
				crypto_key = crypto_key + special_symbols[key_seed];
				special_symbols_count++;
				countingLengthCryptoKey++;
				break;
        }
    }

    cout << "\n-----------------------------\n";
    cout << "      Cryptography Key         \n";
    cout << "------------------------------\n\n";
    cout << " " << crypto_key;
    cout << "\n\nPress any key to continue... \n";
    getchar();
}

int main()
{
    int option;
	int desired_length;
    
	//** designing the menu
    do 
	{
        cout << "\n-------------------------------------\n";
        cout << "  Random Cryptography Key Generator    \n";
        cout << "-------------------------------------\n\n";
        cout << "    1 --> Generate a Cryptography Key"
             << "\n";
        cout << "    2 --> Quit the program"
             << "\n\n";
        cout << "Enter 1 for Generating Cryptograpy Key or 2 to quit the program  : ";
        cin >> option;

        switch (option) 
		{
        case 1:
            cout << "Set the length to :  ";
            cin >> desired_length;
			
            //** if the length entered is less than 7, an error will be shown
            if (desired_length < 7) 
			{
                cout << "\nError Mode : The Cryptography Key Length hould be at least 7\n";
                cout << "Press a key and try again \n";
                getchar();
            }
            //** The desired length should bot be bigger than 100, otherwise an error will be shown
            else if (desired_length > 100) 
			{
                cout << "\nError Mode : The maximum length of the cryptography key should be 100\n";
                cout << "Press a key and try again \n";
                getchar();
            }
			
            //** in ohter cases, call generate_crypto_key() function to generate a cryptography key
            else
                generate_crypto_key(desired_length);
            break;

        default:
            //** in case if an invalid option is entered, show to the user an error message
            if (option != 2) 
			{
                printf("\nOups! You have entered a choice that doesn't exist\n");
                printf("Enter ( 1 ) to generate cryptography key and ( 2 ) to quit the program.\n");
                cout << "Enter a key and try again \n";
                getchar();
            }
            break;
        }
    } while (option != 2);

    return 0;
}