#include "Octagon.hpp"
#include <iostream>
#include <stdexcept>

// Конструкторы
Octagon::Octagon() noexcept : Figure(8) {}

Octagon::Octagon(const Octagon& other) noexcept : Figure(other) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

Octagon::Octagon(const std::initializer_list<std::pair<double, double>>& points) : Octagon() {
    if (points.size() != 8) {
        throw std::runtime_error("Trying initialize octagon with not 8 points.");
    }
    std::copy(points.begin(), points.end(), this->points_);
}

// Переопределённый оператор присваивания
Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        std::copy(other.points_, other.points_ + other.vertices_number_, this->points_);
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
        in >> o.points_[i];
    }
    return in;
}
