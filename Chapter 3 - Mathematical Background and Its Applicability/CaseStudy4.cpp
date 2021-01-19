#include <bits/stdc++.h> 

using namespace std; 
  
//** the below function is used 
//** for computing the variance 
int computingVariance(int n[], int h) 	//**a=n, n=h
{ 
    //** will compute the mean
	//** average of the elements
    int sum = 0; 
    for (int k = 0; k < h; k++) 
        sum += n[k]; 
    double theMean = (double)sum /  
                     (double)h; 
  
    //** calculate the sum squared  
    //** differences with the mean 
    double squared_differences = 0; 
    for (int t=0; t<h; t++)  
        squared_differences += (n[t] - theMean) *  
							   (n[t] - theMean); 
    return squared_differences / h; 
} 
  

int main() 
{ 
    int arr[] = {600, 470, 170, 430, 300}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    cout << "The variance is: "
         << computingVariance(arr, n) << "\n";    
    return 0; 
} 