#include<iostream> 
using namespace std; 
  
//** function for computing extended
//** euclidean algorithm
int gcd_e(int x, int y, int *w, int *z); //a=x, b=y, *x=*w, *y=*z, gcdExtended=gcd_e

void modulo_inverse(int h, int modulo)			//a = h, m=modulo
{ 
    int i, j; 								//x=i, y=j
    int g = gcd_e(h, modulo, &i, &j); 
    if (g != 1) 
        cout << "There is no inverse."; 
    else
    { 
        //** we add the modulo in
		//** order to handle negative i
        int result = (i%modulo + modulo) % modulo; 
        cout << "The modular multiplicative inverse is " << result; 
    } 
} 
  
// C function for extended Euclidean Algorithm 
int gcd_e(int h, int k, int *w, int *z) //** a=h, b=k, *x=*w, *y=*z
{ 
    //** the "happy" case 
    if (h == 0) 
    { 
        *w = 0, *z = 1; 
        return k; 
    } 
  
	//** storing results of our recurive invoke
    int a1, b1; 	//** x1=a1, y1=b1
    int g = gcd_e(k%h, h, &a1, &b1); 
  
    //** with recursive invocation results
	//** we will update x and y 
    *w = b1 - (k/h) * a1; 
    *z = a1; 
  
    return g; 
} 
  

int main() 
{ 
    int x = 3, modulo = 11; 
    modulo_inverse(x, modulo); 
    return 0; 
} 
