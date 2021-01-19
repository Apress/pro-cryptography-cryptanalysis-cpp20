#include <iostream>
#include <random>

int main()
{
  const int number_of_experiments=10000;
  const int number_of_stars_distribution=100;    // maximum number of stars to distribute

  std::default_random_engine theGenerator;
  std::chi_squared_distribution<double> theDistribution(6.0);

  int p[10]={};

  for (int i=0; i<number_of_experiments; ++i) 
  {
    double no = theDistribution(theGenerator);
    if ((no>=0.0)&&(no<10.0)) ++p[int(no)];
  }

  std::cout << "chi_squared_distribution (6.0):" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*number_of_stars_distribution/number_of_experiments,'*') << std::endl;
  }

  return 0;
}