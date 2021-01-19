#include <iostream>
#include <string>
#include <random>

int main()
{
  //** the constant represents the number of experiments
  const int numberOfExperiments=10000;  
  //** the constant represents the
  //** maximum number of stars to distribute
  const int numberOfStarsToDistribute=100;    

  std::default_random_engine g;
  std::normal_distribution<double> dist(6.0,3.0);

  int prob[10]={};

  for (int k=0; k<numberOfExperiments; ++k) {
    double no = dist(g);
    if ((no>=0.0)&&(no<10.0)) ++prob[int(no)];
  }

  std::cout << "the mean distribution (6.0,3.0):" << std::endl;

  for (int l=0; l<10; ++l) {
    std::cout << l << "-" << (l+1) << ": ";
    std::cout << std::string(prob[l]*numberOfStarsToDistribute/numberOfExperiments,'*') << std::endl;
  }

  return 0;
}