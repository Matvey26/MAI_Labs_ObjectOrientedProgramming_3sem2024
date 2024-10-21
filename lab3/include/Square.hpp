#pragma once
#include "Figure.hpp"

class Square : public Figure {
public:
    // Конструкторы
    Square() noexcept;
    Square(Point* points) noexcept;
    Square(const Square& other) noexcept;
    ~Square() noexcept;

    // Переопределённые методы
    Square& operator=(const Square& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Square& s);
    friend std::istream& operator>>(std::istream& in, Square& s);

private:
    static constexpr size_t vertices_number_ = 4;  // Количество вершин квадрата
    Point* points_;
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Square& s);
std::istream& operator>>(std::istream& in, Square& s);
