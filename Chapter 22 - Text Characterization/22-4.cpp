#include <iostream> 
using namespace std; 
  
void printTrigramOccurance(string fullText, string trigramPattern)
{ 	
    int occurance = fullText.find(trigramPattern); 
    while (occurance!= string::npos) 
    { 
        cout << "Pattern found at index " << occurance << endl; 
        occurance = fullText.find(trigramPattern, occurance + 1); 
    }
} 
int main() 
{ 
    string fullText = "Welcome to Apress.";
    string trigramPattern = "Apr"; 
    printTrigramOccurance(fullText, trigramPattern);     
} 
