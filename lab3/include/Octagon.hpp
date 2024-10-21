#pragma once
#include "Figure.hpp"

class Octagon : public Figure {
public:
    // Конструкторы
    Octagon() noexcept;
    Octagon(const Octagon& other) noexcept;

    // Переопределённые методы
    Octagon& operator=(const Octagon& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Octagon& o);
    friend std::istream& operator>>(std::istream& in, Octagon& o);
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Octagon& o);
std::istream& operator>>(std::istream& in, Octagon& o);
