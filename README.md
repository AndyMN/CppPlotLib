# CppPlotLib
Matlab plotting syntax in C++ using Gnuplot

When Gnuplot is installed this library can be used inside of your C++ program to plot using Matlab syntax. 

It uses a pipe to Gnuplot. 

It will be able to do "all" the plots Matlab can. 

This was created because plotting in C++ is always annoying.


Usage example:

````cpp
#include <vector>
#include "Figure.h"

int main() {
  std::vector<double> x = {1, 2, 3};
  std::vector<double> y = {2, 4, 6};
  
  Figure fig1;
  fig1.plot(x,y);
  fig1.show();

  return 0;
}
````
