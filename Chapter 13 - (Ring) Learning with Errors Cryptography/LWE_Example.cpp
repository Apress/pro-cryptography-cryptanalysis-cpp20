#include <iostream>
#include <math.h> 
#include <ctime>
using namespace std;

int main()
{   
    srand(time(0));

    int numberOfRandVals = 20;
    int values_A [20]; //** values_A is a set of random numbers; represents the public key     
    int secretValue = 5; //** represents the secret key
    int values_error [numberOfRandVals]; //** represents the error values
    int values_B [numberOfRandVals]; //** values_B is computed based on values_A, secretValue, values_error; represents the public key

    int q = 97; //** q is a prime number
    
    //** generate random values
    //** the number of random values is numberOfRandVals = 20
    //** the range is 0 - q=97
    for(int i=0; i < numberOfRandVals; i++) 
    {
        //** to generate a random value in a range MIN - MAX,
        //** we proceed as folloes: val = rand() % (MAX + 1 - MIN) + MIN;
        
        //** generate random values between 0 - 97
        values_A[i] = rand() % (q + 1 - 0) + 0;  
        //** generate small error values, between 1 - 4 
        values_error[i] = rand() % (4 + 1 - 1) + 1;
        //** compute values_B using the formula B_i = A_i*s + e_i
        values_B[i] = values_A[i]*secretValue + values_error[i];
    }

    cout<<"--------- The parameters and the keys ---------" << endl;
    cout<<"--Prime number (q)--" << endl;
    cout<<"q = " << q << endl;
    cout<<"--Public key (A, B)--" << endl;
    cout<<"A = [ ";
    for (int i=0; i < numberOfRandVals; i++)
    {
        cout << values_A[i] << " ";
    }
    cout<<"]" << endl;

    cout<<"B = [ ";
    for (int i=0; i < numberOfRandVals; i++)
    {
        cout << values_B[i] << " ";
    }
    cout<<"]" << endl;
    cout<<"--Secret key (s)--" << endl;
    cout<<"s = " << secretValue << endl;
    cout<<"--Random error (e)--" << endl;
    cout<<"e = [ ";
    for (int i=0; i < numberOfRandVals; i++)
    {
        cout << values_error[i] << " ";
    }
    cout<<"]" << endl;

    cout<< endl << endl << "--------- Getting samples from the public key... ---------";
    int noOfSamples = floor(numberOfRandVals / 4); //** represents the number of samples from the public key
    int samples [noOfSamples]; 
    for(int i=0; i < noOfSamples; i++) 
    {        
        //** generate a number of 5 random indices between 0 and 19        
        samples[i] = rand() % ((numberOfRandVals-1) + 1 - 0) + 0;
    }
    cout<<endl<<"--Sample indices--";
    cout<<endl<<"samples = [ ";
    for (int i=0; i < noOfSamples; i++)
    {
        cout << samples[i] << " ";
    }
    cout<<" ]" << endl;
    cout<<"--Sample pairs--";    
    for (int i=0; i < noOfSamples; i++)
    {
        cout << endl <<"Sample " << i << ": [" 
        << values_A[samples[i]] << " " << values_B[samples[i]] << "]";
    }

    cout<< endl << endl << "--------- Computing u and v... ---------";    
    int message = 0; //** the message to be encrypted can be a value from {0, 1}
    int u = 0, v = 0;
    //** u = (sum (samples from values_A)) mod q
    //** v = (sum (samples from values_B) + [q/2] * message) mod q
    for (int i=0; i < noOfSamples; i++)
    {
        u = u + values_A[samples[i]]; 
        v = v + values_B[samples[i]];
    }

    v = v + floor(q/2) * message;

    u = u % q;
    v = v % q;

    cout<<endl<<"u = "<<u;
    cout<<endl<<"v = "<<v;
    
    cout<< endl << endl << "--------- Encrypting... ---------";
    
    cout<<endl<<"--Message--";
    cout<<endl<<"m = "<<message;
    cout<<endl<<"--Encryption f the message--";
    cout<<endl<<"Enc(m) = (" << u << ", " << v <<")";

    cout<< endl << endl << "--------- Decrypting... ---------";
    int result = (v - secretValue * u) % q;    
   
    int decryption;
    if (result > q/2)
        decryption = 1;
    else
        decryption  = 0;
    cout<<endl<<"The message is: " << decryption;

    return 0;   
}