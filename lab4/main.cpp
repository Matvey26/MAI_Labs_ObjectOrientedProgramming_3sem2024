#include "Array.hpp"
#include "Figure.hpp"
#include "NAngle.hpp"
#include <iostream>

int main() {
    Figure<int> fig;
    std::cin >> fig;
    std::cout << fig << std::endl;

    Triangle<int> tr;
    std::cin >> tr;
    std::cout << tr << std::endl;
    return 0;
}