#pragma once
#include "Figure.hpp"

class Triangle : public Figure {
public:
    // Конструкторы
    Triangle() noexcept;
    Triangle(Point* points) noexcept;
    Triangle(const Triangle& other) noexcept;
    ~Triangle() noexcept;

    // Переопределённые методы
    Triangle& operator=(const Triangle& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Triangle& t);
    friend std::istream& operator>>(std::istream& in, Triangle& t);

private:
    static constexpr size_t vertices_number_ = 3;  // Количество вершин треугольника
    Point* points_;
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Triangle& t);
std::istream& operator>>(std::istream& in, Triangle& t);
