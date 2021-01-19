//** NOTE: bits/stdc++ does not represent 
//** a standard header file of GNU C++ library.
//** If the code will be compiled with other
//** compilers than GCC it will fail
#include <bits/stdc++.h>

using namespace std; 
  
//** the function will compute 
//** the GCD for two number
int g(int x, int y) 
{ 
    if (x == 0) 
        return y; 
    return g(y % x, x); 
} 
  

int main() 
{ 
    int x = 10, y = 15; 
    cout << "Euclid GCD(" << x << ", " 
         << y << ") = " << g(x, y)  
                        << endl; 
    x = 35, y = 10; 
    cout << "Euclid GCD(" << x << ", " 
         << y << ") = " << g(x, y)  
                        << endl; 
    x = 31, y = 2; 
    cout << " EuclidGCD(" << x << ", " 
         << y << ") = " << g(x, y)  
                        << endl; 
    return 0; 
} 