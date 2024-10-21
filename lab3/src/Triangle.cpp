#include "Triangle.hpp"
#include <iostream>

// Конструкторы
Triangle::Triangle() noexcept : Figure(3) {}

Triangle::Triangle(const Triangle& other) noexcept : Figure(other) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

// Переопределённый оператор присваивания
Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        Figure::operator=(other);
        for (size_t i = 0; i < vertices_number_; ++i) {
            points_[i] = other.points_[i];
        }
    }
    return *this;
}

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& out, const Triangle& t) {
    out << "Triangle(";
    for (size_t i = 0; i < t.vertices_number_; ++i) {
        out << t.points_[i];
        if (i < t.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Triangle& t) {
    for (size_t i = 0; i < t.vertices_number_; ++i) {
        std::cin >> t.points_[i];
    }
    return in;
}
