#include <iostream>
#include <cmath>

using namespace std;

float computeStandardDeviation(float data[]);

int main()
{
    int n;
    float elements_array[10];

    cout << "Add 10 elements: ";
    for(n = 0; n < 10; ++n)
        cin >> elements_array[n];

    cout << endl << "The Standard Deviation is = " << computeStandardDeviation(elements_array);

    return 0;
}

float computeStandardDeviation(float elements_array[])
{
    float theSum = 0.0, theMean, theStandardDeviation = 0.0;

    int j,k;

    for(j = 0; j < 10; ++j)
    {
        theSum += elements_array[j];
    }

    theMean = theSum/10;

    for(k = 0; k < 10; ++k)
        theStandardDeviation += pow(elements_array[k] - theMean, 2);

    return sqrt(theStandardDeviation / 10);
}