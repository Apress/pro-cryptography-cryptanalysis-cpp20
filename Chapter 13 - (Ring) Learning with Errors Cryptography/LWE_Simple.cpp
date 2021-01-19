#include <iostream>
#include <math.h> 
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    int no_of_values = 10;
    int public_key [no_of_values];
    int values [no_of_values];  
    int secret_key = 5;
    int error_value = 12;
    int message = 1;

    int value = 0;

    for (int i = 0; i < no_of_values; i++)
    {
        //** generate random values between 0 and 23
        values[i] = rand() % (23 + 1 - 0) + 0; 
        //** compute the public key 
        public_key[i] = values[i] * secret_key + error_value;        
    }

    cout<<"--Message: "<< message<<"--";
    cout<<endl<<"--Random values--"<<endl;
    for(int i = 0; i < no_of_values; i++)
    {
        cout<<values[i]<<" ";
    }

    cout<<endl<<"--Public Key--"<<endl;
    for(int i = 0; i < no_of_values; i++)
    {
        cout<<public_key[i]<<" ";
    }

    //** get half random samples from the public_key
    int noOfSamples = floor(no_of_values / 2);
    int samples [noOfSamples]; 
    for(int i=0; i < noOfSamples; i++) 
    {        
        //** generate a number of 5 random indices between 0 and 10        
        samples[i] = rand() % ((no_of_values-1) + 1 - 0) + 0;
    }
    cout<<endl<<"--Sample indices--";
    cout<<endl<<"samples = [ ";
    for (int i=0; i < noOfSamples; i++)
    {
        cout << samples[i] << " ";
    }
    cout<<" ]" << endl;

    int sum = 0;
    for (int i = 0; i < noOfSamples; i++)
    {
        sum += public_key[samples[i]];
    }

    cout<<endl<<"--The sum: " << sum << "--";

    if (message == 1)
        sum+=1;

    cout<<endl<<"--The encryption of the message is:" << sum <<" --";

    int decryption = sum % secret_key;

    if (decryption % 2 == 0)
        cout<<endl<<"--The decryption is: 0--";
    else
        cout<<endl<<"--The decryption is: 1--";



    return 0;
}