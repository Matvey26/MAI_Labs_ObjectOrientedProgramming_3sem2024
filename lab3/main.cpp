#include "Array.hpp"
#include "Figure.hpp"
#include "Octagon.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include <iostream>

std::ostream& PrintFigures(std::ostream& out, const Array<Figure*>& figures_pointers) {
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        out << "Figure #" << i << ": " << *figures_pointers[i] << '\n';
    }
    return out;
}

std::ostream& PrintFiguresArea(std::ostream& out, const Array<Figure*>& figures_pointers) {
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        out << "Figure #" << i << ": " << static_cast<double>(*figures_pointers[i]) << '\n';
    }
    return out;
}

double GetTotalArea(const Array<Figure*>& figures_pointers) {
    double result = 0.0;
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        result += static_cast<double>(*figures_pointers[i]);
    }

    return result;
}

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

    Array<Figure*> figures(3);
    figures[0] = &oct;
    figures[1] = &trg;
    figures[2] = &sqr;

    std::cout << figures.Size() << '\n';

    PrintFigures(std::cout, figures) << '\n';
    PrintFiguresArea(std::cout, figures) << '\n';
    std::cout << "Total area: " << GetTotalArea(figures) << '\n';

    std::cout << "Проверяем, что сравнение фигур работает:\n";
    Figure lol1 = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    Figure lol2 = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    std::cout << (lol1 == lol2) << '\n';

    return 0;
}