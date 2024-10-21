#pragma once
#include "Figure.hpp"

class Octagon : public Figure {
public:
    // Конструкторы
    Octagon() noexcept;
    Octagon(Point* points) noexcept;
    Octagon(const Octagon& other) noexcept;
    ~Octagon() noexcept;

    // Переопределённые методы
    Octagon& operator=(const Octagon& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Octagon& o);
    friend std::istream& operator>>(std::istream& in, Octagon& o);

private:
    static constexpr size_t vertices_number_ = 8;  // Количество вершин восьмиугольника
    Point* points_;  // Указатель на массив точек
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Octagon& o);
std::istream& operator>>(std::istream& in, Octagon& o);
