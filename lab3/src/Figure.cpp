#include "Figure.hpp"
#include <initializer_list>
#include <utility>
#include <iostream>

// Конструкторы и деструктор
Figure::Figure() noexcept
    : vertices_number_(0)
    , points_(nullptr)
{}

Figure::Figure(size_t vertices_number, Point* points) noexcept
    : vertices_number_(vertices_number)
    , points_(new Point[this->vertices_number_])
{
    for (size_t i = 0; i < vertices_number; ++i) {
        this->points_[i] = points[i];
    }
}

Figure::Figure(std::initializer_list<std::pair<double, double>> points) noexcept
    : vertices_number_(points.size())
    , points_(new Point[this->vertices_number_]) 
{
    size_t i = 0;
    for (auto point : points) {
        this->points_[i] = Point(point);
        ++i;
    }
}

Figure::Figure(const Figure& other) noexcept
    : vertices_number_(other.vertices_number_)
    , points_(new Point[this->vertices_number_])
{
    for (size_t i = 0; i < other.vertices_number_; ++i) {
        this->points_[i] = other.points_[i];
    }
}

Figure::Figure(Figure&& other) noexcept
    : vertices_number_(other.vertices_number_)
    , points_(other.points_)
{
    other.vertices_number_ = 0;
    other.points_ = nullptr;
}

Figure::~Figure() noexcept {
    delete[] this->points_;
}

// Геттеры
std::pair<double, double> Figure::GetCenter() const noexcept {
    Point center;
    for (size_t i = 0; i < this->vertices_number_; ++i) {
        center += this->points_[i];
    }
    center /= this->vertices_number_;

    return static_cast<std::pair<double, double>>(center);
}

size_t Figure::GetVerticesNumber() const noexcept {
    return this->vertices_number_;
}

Point* Figure::GetVertices() noexcept {
    return this->points_;
}

// Операторы
Figure::operator double() const noexcept {
    double result = 0.0;
    Point first = this->points_[0];
    Point second = this->points_[1];
    for (size_t i = 2; i < this->vertices_number_; ++i) {
        Point third = this->points_[i];
        result += 0.5 * (second - third).Length() * DistanceDotLine(first, second, third);
        second = third;
    }

    return result;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        delete[] this->points_;
        this->vertices_number_ = other.vertices_number_;
        this->points_ = new Point[this->vertices_number_];
        for (size_t i = 0; i < this->vertices_number_; ++i) {
            this->points_[i] = other.points_[i];
        }
    }

    return *this;
}

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Figure& f) {
    out << "Figure(";
    for (size_t i = 0; i < f.vertices_number_; ++i) {
        out << f.points_[i];
        if (i < f.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Figure& f) {
    size_t vertices_number;
    in >> vertices_number;
    Point* points = new Point[vertices_number];
    for (size_t i = 0; i < vertices_number; ++i) {
        std::cin >> points[i];
    }
    f = Figure(vertices_number, points);
    delete[] points;
    return in;
}
