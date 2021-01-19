#include <bits/stdc++.h>  
using namespace std; 
  
//** computing extended euclidean algorithm
int g_e(int x, int y, int *w, int *y)  
{  
    //** this is the basic or ideal case
    if (x == 0)  
    {  
        *w = 0;  
        *y = 1;  
        return y;  
    }  
  
	//** variables for storing the results
	//** for the recursive call
    int a1, b1;   
    int g = g_e(y%x, x, &a1, &b1);  
  
    //** with help of the recursive call
	//** update a and b with the results  
    *w = b1 - (y/x) * a1;  
    *y = a1;  
  
    return g;  
}  
  
// Driver Code 
int main()  
{  
    int a, b, w = 35, y = 15;  
    int g = g_e(w, y, &a, &b);  
    cout << "g_e(" << w << ", " << y  
         << ") = " << g << endl; 
    return 0;  
}  