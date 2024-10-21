#include "Octagon.hpp"
#include <iostream>

// Конструкторы
Octagon::Octagon() noexcept : Figure(8) {}

Octagon::Octagon(const Octagon& other) noexcept : Figure(other) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

// Переопределённый оператор присваивания
Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        Figure::operator=(other);
        for (size_t i = 0; i < vertices_number_; ++i) {
            points_[i] = other.points_[i];
        }
    }
    return *this;
}

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& out, const Octagon& o) {
    out << "Octagon(";
    for (size_t i = 0; i < o.vertices_number_; ++i) {
        out << o.points_[i];
        if (i < o.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Octagon& o) {
    for (size_t i = 0; i < o.vertices_number_; ++i) {
        std::cin >> o.points_[i];
    }
    return in;
}
