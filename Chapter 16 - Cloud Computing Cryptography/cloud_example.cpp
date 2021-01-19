#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// the encryption scheme is a simple XOR-ing process
// XOR-ing is used for both encryption and decryption
// parameter "message" can be the plain message or the encrypted message, according to user's needs
string xor_string(string message, string key)
{
    string out_message(message);
    unsigned int key_len(key.length()), message_len(message.length()), pos(0);
    for(unsigned int index = 0; index < message_len; index++)
    {
        out_message[index] = message[index] ^ key[pos];
        if(++pos == key_len){ pos = 0; }
    }
    return out_message;
}
    
int main()
{
    // read the message to be encrypted from the console
    string plain_text;
    cout<<"Enter the message: ";
    getline (cin, plain_text);
    
    // the public key is read from the .pem corresponding file
    string row1;
    string public_key = "";
    ifstream public_key_file ("publicKey.pem");
    if (public_key_file.is_open())
    {
        while (getline (public_key_file, row1) )
        {
            public_key += row1;
        }
        public_key_file.close();
    }
    // to check that the public key is read correctly, it is dispalyed on the console
    cout<<"Public key:"<<endl<<public_key<<endl<<endl;


    // the private key is read from the .pem corresponding file
    string row2;
    string private_key = "";
    ifstream private_key_file ("privateKey.pem");
    if (private_key_file.is_open())
    {
        while (getline (private_key_file, row2) )
        {
            private_key += row2;
        }
        private_key_file.close();
    }
    // to check that the public key is read correctly, it is dispalyed on the console
    cout<<"Private key:"<<endl<<private_key<<endl<<endl;

    // the encryption of the plain message is stored into encrypted_message
    string encrypted_text = xor_string(plain_text, public_key);
    cout << endl << "The encryption of the message is: " << endl << encrypted_text << endl;
        
    
    // to decrypt the message, the receiver should proceed with some steps
    // 1. the receiver should xor his/her private key with his/her public key 
    string xor_keys = xor_string(public_key, private_key);
       
    // 2. the receiver should xor the encrypted text with the result from the step 1
    string xor_result = xor_string(encrypted_text, xor_keys);
       
    // 3. the decryption is made by xor-ing the result from previous step with the private key 
    string decrypted_message = xor_string(xor_result, private_key);
        
    cout << endl << "The decryption of the message is:  " << endl << decrypted_message << endl;
    return 0;
}