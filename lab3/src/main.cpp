#include "../include/lab.h"
#include <cmath>
#include <float.h>

// Определения методов класса Point

Point::Point() : x_(0.0), y_(0.0) {}

Point::Point(double number) : x_(number), y_(number) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

Point::Point(const std::pair<double, double>& p) : x_(p.first), y_(p.second) {}

Point::Point(const Point& other) : x_(other.x_), y_(other.y_) {}

Point Point::operator+(const Point& other) const {
    return Point(x_ + other.x_, y_ + other.y_);
}

Point& Point::operator+=(const Point& other) {
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

Point Point::operator-(const Point& other) const {
    return Point(x_ - other.x_, y_ - other.y_);
}

Point& Point::operator-=(const Point& other) {
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

Point Point::operator*(double scalar) const {
    return Point(x_ * scalar, y_ * scalar);
}

Point& Point::operator*=(double scalar) {
    this->x_ *= scalar;
    this->y_ *= scalar;
    return *this;
}

Point Point::operator/(double scalar) const {
    return Point(x_ / scalar, y_ / scalar);
}

Point& Point::operator/=(double scalar) {
    this->x_ /= scalar;
    this->y_ /= scalar;
    return *this;
}

double Point::dot(const Point& other) const {
    return x_ * other.x_ + y_ * other.y_;
}

double Point::cross(const Point& other) const {
    return x_ * other.y_ - y_ * other.x_;
}

double& Point::operator[](int index) {
    if (index == 0) return x_;
    if (index == 1) return y_;
    throw std::out_of_range("Index out of range");
}

double Point::operator[](int index) const {
    if (index == 0) return x_;
    if (index == 1) return y_;
    throw std::out_of_range("Index out of range");
}

double Point::Length() const {
    return std::sqrt(this->dot(*this));
}

double Point::AngleBetweenPoints(const Point& other) {
    double cos_theta = this->dot(other) / (this->Length() * other.Length());
    double theta = std::acos(cos_theta);

    if (this->cross(other) < 0) {
        theta = 2 * M_PI - theta;
    }

    return theta;
}

Point::operator std::pair<double, double>() const {
    return {x_, y_};
}

// Определения методов шаблонного класса NAngle

template <size_t N>
NAngle<N>::NAngle(std::initializer_list<std::pair<double, double>> points) 
    : center_(0.0, 0.0), phi_(2 * M_PI), side_(DBL_MAX) {
    
    // Находим центр фигуры
    for (auto p : points) {
        this->center_ += Point{p};
    }
    this->center_ /= N;

    // Находим угол наклона фигуры
    Point Oy{0, 1};
    double offset = (N % 2 == 0 ? M_PI / N : 0.0);
    for (auto p : points) {
        double cur_angle = Oy.AngleBetweenPoints(Point{p} - this->center_) + offset - 2 * M_PI;
        if (cur_angle < 0.0) {
            cur_angle += 2 * M_PI;
        }
        this->phi_ = std::min(this->phi_, cur_angle);
    }

    // Вычисляем сторону
    auto it = points.begin();
    Point first = *it;
    for (++it; it != points.end(); ++it) {
        this->side_ = std::min(this->side_, (first - Point{*it}).Length());
    }
}

template <size_t N>
NAngle<N>::NAngle(const NAngle& other) noexcept 
    : center_(other.center_), phi_(other.phi_), side_(other.side_) {}

template <size_t N>
NAngle<N>::NAngle(NAngle&& other) noexcept 
    : center_(other.center_), phi_(other.phi_), side_(other.side_) {
    other.center_ = Point{};
    other.phi_ = 0.0;
    other.side_ = 0.0;
}

template <size_t N>
NAngle<N>& NAngle<N>::operator=(const NAngle& other) noexcept {
    if (this != &other) {
        this->center_ = other.center_;
        this->phi_ = other.phi_;
        this->side_ = other.side_;
    }
    return *this;
}

template <size_t N>
NAngle<N>& NAngle<N>::operator=(NAngle&& other) noexcept {
    if (this != &other) {
        this->center_ = other.center_;
        this->phi_ = other.phi_;
        this->side_ = other.side_;

        other.center_ = Point{};
        other.phi_ = 0.0;
        other.side_ = 0.0;
    }
    return *this;
}

template <size_t N>
std::pair<double, double> NAngle<N>::GetCenter() const noexcept {
    return this->center_;
}

template <size_t N>
NAngle<N>::operator double() const noexcept {
    return N * (this->side_ * this->side_) / (4 * std::tan(M_PI / N));
}

template <size_t N>
std::ostream& operator<<(std::ostream& out, const NAngle<N>& f) {
    out << "NAngle with center at: " << f.center_ << " and side length: " << f.side_;
    return out;
}

template <size_t N>
std::istream& operator>>(std::istream& in, NAngle<N>& f) {
    // Реализация ввода для NAngle
    return in;
}
