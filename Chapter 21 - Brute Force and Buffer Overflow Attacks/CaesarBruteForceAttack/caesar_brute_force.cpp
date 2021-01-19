#include<iostream>
using namespace std;

// the function will be used to encrypt the plaintext
// string msg - the message
// int keytValue - the key
string encrypt(string msg,int keyValue)
{
	// variable used to hold the cipher value of the plaintext
    string cipher="";

	// parse the string
    for(int i=0;i<msg.length();i++)
    {
		// verify if the character is upper case
        if(isupper(msg[i]))
			// add to the cipher the character plus the key and subtract ASCII 65 value ('A'). 
			// the value obtained do modulo 26 (english alphabet letters) and add ASCII value 65 back.
            cipher += (msg[i] + keyValue - 65)%26 + 65;		
		
		// verify if the character is lower case
        else if(islower(msg[i]))
			//** the same as above. ASCII value 97 ('a')
            cipher += (msg[i] + keyValue - 97)%26 + 97;
        else
            cipher += msg[i];
    }
    return cipher;
}

// The decryption will be done using the brute force attack by
// checking all possible keys
// string encMessage - the encrypted message
void decrypt(string encMessage)
{
	// the variable for storing the plaintext
    string plaintext;
	
	// we will try for each key and we will do the decryption
    for(int keyTry=0;keyTry<26;keyTry++)
    {
        plaintext = "";
		// parse accordingly based on the message length
        for(int i=0;i<encMessage.length();i++)
        {
			// check if the character is upper case
            if(isupper(encMessage[i]))
            {
                if((encMessage[i] - keyTry - 65)<0)
                    plaintext += 91 + (encMessage[i] - keyTry - 65);
                else
                    plaintext += (encMessage[i] - keyTry - 65)%26 + 65;
            }
			// check if the character is lower case
            else if(islower(encMessage[i]))
            {
                if((encMessage[i] - keyTry - 97) < 0)
                    plaintext += 123 + (encMessage[i] - keyTry - 97);
                else
                    plaintext += (encMessage[i] - keyTry - 97)%26 + 97;
            }
            else
                plaintext += encMessage[i];
        }
        cout << "BRUTE-FORCE ATTACK (DECRYPTION) - The clear text for key -> " << keyTry << " :- " << plaintext << endl;
    }
}

int main()
{
	int encKey;
	string cleartext;
	cout << "ENCRYPTION - Enter the text for encryption -> ";
	getline(cin,cleartext);
	
	cout << "Enter the key for encryption the text -> ";
	cin >> encKey;

	string encryptedMessage = encrypt(cleartext,encKey);
	cout << "ENCRYPTED MESSAGE - The encrypted message is -> " << encryptedMessage << endl << endl;
	
	//** brute force attack
	decrypt(encryptedMessage);
}