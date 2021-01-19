#include <iostream>
#include "legendre.h"

using namespace std ;
using namespace LegendreStorage::Legendre ;

int main()
{
  double p_n;

  cout.precision(5) ;
  for (unsigned int v = 0 ; v <= 5 ; v++)
  {
    for (double b = -1.0 ; b <= 1.0 ; b = b + 0.1)
    { 
      p_n = Polynom_n<double>(v, b) ;
      cout << "P" << v << "(" << b << ") = " << p_n << endl ;
    }
    cout << endl ;
  }

  return 0 ;
}