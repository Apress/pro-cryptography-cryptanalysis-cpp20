#include<iostream> 
using namespace std; 
  
//** this represents the basic method or tricky method
//** for finding modulo multiplicative inverse of 
//** x under modulo m 
int modulo_inverse(int x, int m) 
{ 
    x = x%m; 
    for (int y=1; y<m; y++) 
       if ((x*y) % m == 1) 
          return y; 
} 
  

int main() 
{ 
    int x = 3, m = 11; 
    cout << modulo_inverse(x, m); 
    return 0; 
} 