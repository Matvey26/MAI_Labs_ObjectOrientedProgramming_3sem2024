#include "Figure.hpp"
#include "Octagon.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include <iostream>

int main() {
    Octagon oct;
    Triangle trg;
    Square sqr;

    std::cout << "Фигуры вводятся путём перечисления координат их точек по порядку." << std::endl;
    std::cout << "Введите три фигуры:" << std::endl;
    
    std::cout << "1. Восьмиугольник:" << std::endl;
    std::cin >> oct;

    std::cout << "2. Треугольник:" << std::endl;
    std::cin >> trg;

    std::cout << "3. Квадрат:" << std::endl;
    std::cin >> sqr;

    return 0;
}