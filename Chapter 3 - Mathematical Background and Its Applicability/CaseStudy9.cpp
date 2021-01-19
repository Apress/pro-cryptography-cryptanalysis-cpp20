#include<bits/stdc++.h>

using namespace std;  

int inverse(int x, int modulo) 			//** a=x, m=modulo
{ 
    int modulo0 = modulo, k, quotient; 				//** m0 = modulo0, t=k, q=l
    int a0 = 0, a1 = 1;								//** x0=a0, x1=a1
  
    if (modulo == 1) 
       return 0; 
  
    //** we will apply extended euclidean algorithm
    while (x > 1) 
    {         
        quotient = x / modulo; 
  
        k = modulo; 
  
        //** modulo represents the remainder
		//** continue with the process same as 
        //** euclid's algorithm
        modulo = x%modulo, x=k; 
  
        k = a0; 
  
        a0 = a1 - quotient * a0; 
  
        a1 = k; 
    } 
  
    //** make a1 positive 
    if (a1 < 0) 
       a1 += modulo0; 
  
    return a1; 
} 

int lookForMinX(int numbers[], int remainders[], int l) //num=numbers rem=remainders, k=l
{ 
    //** computing the product for all the numbers
    int product = 1; 
    for (int j = 0; j < l; j++) 
        product *= numbers[j]; 
  
    //** we initialize the result with 0
    int result = 0; 
  
    //** apply the formula mentioned above
    for (int j = 0; j < l; j++) 
    { 
        int pp = product / numbers[j]; 
        result += remainders[j] * inverse(pp, numbers[j]) * pp; 
    } 
  
    return result % product; 
} 
  

int main(void) 
{ 
    int numbers[] = {3, 4, 5}; 
    int remainders[] = {2, 3, 1}; 
    int k = sizeof(numbers)/sizeof(numbers[0]); 
    cout << "x is " << lookForMinX(numbers, remainders, k); 
    return 0; 
} 