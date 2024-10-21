#include "Square.hpp"
#include <iostream>

// Конструкторы
Square::Square() noexcept : Figure(4) {}

Square::Square(const Square& other) noexcept : Figure(other) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

// Переопределённый оператор присваивания
Square& Square::operator=(const Square& other) {
    if (this != &other) {
        Figure::operator=(other);
        for (size_t i = 0; i < vertices_number_; ++i) {
            points_[i] = other.points_[i];
        }
    }
    return *this;
}

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& out, const Square& s) {
    out << "Square(";
    for (size_t i = 0; i < s.vertices_number_; ++i) {
        out << s.points_[i];
        if (i < s.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Square& s) {
    for (size_t i = 0; i < s.vertices_number_; ++i) {
        std::cin >> s.points_[i];
    }
    return in;
}
