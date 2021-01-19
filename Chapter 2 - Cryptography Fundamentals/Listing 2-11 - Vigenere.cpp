#include <iostream>
#include <string>
using namespace std;
class Vigenere {
   public:
	  //** represents the key 
      string key;
   
	  //** the constructor of the class
	  //** the chosen key
	  Vigenere(string chosenKey) {
      for (int i = 0; i < chosenKey.size(); ++i) {
         if (chosenKey[i] >= 'A' && chosenKey[i] <= 'Z')
            this->key += chosenKey[i];
         else if (chosenKey[i] >= 'a' && chosenKey[i] <= 'z')
            this->key += chosenKey[i] + 'A' - 'a';
      }
   }
   string encrypt(string t)
   {
      string encryptedOutput;
      for (int i = 0, j = 0; i < t.length(); ++i) {
         char c = t[i];
         if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if (c < 'A' || c > 'Z')
            continue;
         encryptedOutput += (c + key[j] - 2 * 'A') % 26 + 'A'; //added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
         j = (j + 1) % key.length();
      }
      return encryptedOutput;
   }
   string decrypt(string t) {
      string decryptedOutput;
      for (int i = 0, j = 0; i < t.length(); ++i) {
         char c = t[i];
         if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if (c < 'A' || c > 'Z')
            continue;
         decryptedOutput += (c - key[j] + 26) % 26 + 'A';//added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
         j = (j + 1) % key.length();
      }
      return decryptedOutput;
   }
};

int main() {
	
   Vigenere myVigenere("APRESS!WELCOME");
   string originalMessage ="ThisisanexampleofvigenerecipherforApress";
   string enc = myVigenere.encrypt(originalMessage);
   string dec = myVigenere.decrypt(enc);
   cout << "Original Message: "<<originalMessage<< endl;
   cout << "Encrypted Message: " << enc << endl;
   cout << "Decrypted Message: " << dec << endl;
}