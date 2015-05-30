#include <iostream>
#include <vector>
#include "Figure.h"
#include <string>

int main() {

    std::vector<double> x = {1, 2, 3 ,4 ,5};
    std::vector<int> y = {2, 4, 6, 8, 10};

    Figure fig1;

    fig1.plot(x, y, "-+");
    fig1.plot(y,x, "+");
    fig1.show();
    fig1.save();


    return 0;
}
