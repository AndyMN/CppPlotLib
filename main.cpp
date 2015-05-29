#include <iostream>
#include <vector>
#include "Figure.h"
#include <string>

int main() {

    std::vector<double> x = {1, 2, 3 ,4 ,5};
    std::vector<int> y = {2, 4, 6, 8, 10};

    Figure fig1;
    fig1.plot(x, y);
    fig1.plot(y, x, "points");
    fig1.show();
    fig1.save();

    Figure fig2;
    fig2.plot(y, x);
    fig2.plot(x, y, "points");
    fig2.show();

    return 0;
}
