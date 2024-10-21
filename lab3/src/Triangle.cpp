#include "Triangle.hpp"
#include <iostream>

// Конструкторы
Triangle::Triangle() noexcept : points_(new Point[vertices_number_]) {}

Triangle::Triangle(Point* points) noexcept
    : Figure(vertices_number_, points), points_(new Point[vertices_number_]) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = points[i];
    }
}

Triangle::Triangle(const Triangle& other) noexcept 
    : Figure(other), points_(new Point[vertices_number_]) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

Triangle::~Triangle() noexcept {
    delete[] points_;
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
