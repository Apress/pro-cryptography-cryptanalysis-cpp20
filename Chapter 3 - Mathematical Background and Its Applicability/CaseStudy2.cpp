//** this will be used for computing the distribution 
#include <random>
#include <iostream> 
  
using namespace std; 
  
int main() 
{ 
    //** declare default_random_engine object 
    //** we will use it as a random number 
    //** we will provide a seed for default_random_engine 
    //** if a pseudo random is necessary
    default_random_engine gen;
  
    double x=0.0, y=1.0;
  
    // Initializing of uniform_real_distribution class 
    uniform_real_distribution<double> dist(x, y); 
  
    //** the number of experiments 
    const int numberOfExperiments = 10000000; 
	
    //** the number of ranges 
    int numberOfRanges = 100; 
    int probability[numberOfRanges] = {}; 
    for (int k = 0; k < numberOfExperiments; ++k) { 
  
        // using operator() function 
        // to give random values 
        double no = dist(gen); 
        ++probability[int(no * numberOfRanges)]; 
    } 
  
    cout << "Probability of some ranges" << endl; 
    // Displaying the probability of some ranges 
    // after generating values 10000 times. 
    cout << "0.50-0.51"
         << " " << (float)probability[50]/(float)numberOfExperiments<<endl; 
    cout << "0.60-0.61"
         << " " << (float)probability[60]/(float)numberOfExperiments<<endl; 
    cout << "0.45-0.46"
         << " " << (float)probability[45]/(float)numberOfExperiments<<endl;
		 
    return 0; 
} 