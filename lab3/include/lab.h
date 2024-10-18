#pragma once
#include <utility>
#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <float.h>
#include <stdexcept>

// Класс двумерной точки (а вообще радиус вектора)
class Point {
public:
    Point();
    Point(double number);
    Point(double x, double y);
    Point(const std::pair<double, double>& p);
    Point(const Point& other);

    // Арифметические операторы
    Point operator+(const Point& other) const;
    Point& operator+=(const Point& other);
    Point operator-(const Point& other) const;
    Point& operator-=(const Point& other);
    Point operator*(double scalar) const;
    Point& operator*=(double scalar);
    Point operator/(double scalar) const;
    Point& operator/=(double scalar);

    // Скалярное произведение
    double dot(const Point& other) const;

    // Векторное произведение для Point (то есть z-компонента векторного произведения)
    double cross(const Point& other) const;

    // Операторы квадратных скобочек для доступа к координатам
    double& operator[](int index);
    double operator[](int index) const;

    // Вычисление длины вектора
    double Length() const;

    // Угол между векторами
    double AngleBetweenPoints(const Point& other);

    // Оператор приведения к std::pair
    operator std::pair<double, double>() const;

private:
    double x_;
    double y_;
};

// Базовый класс фигуры
class Figure {
public:
    virtual std::pair<double, double> GetCenter() const noexcept;
    virtual explicit operator double() const noexcept;
    virtual ~Figure();
};

// Шаблонный класс правильного N-угольника
template <size_t N>
class NAngle : public Figure {
public:
    NAngle(std::initializer_list<std::pair<double, double>> points);
    NAngle(const NAngle& other) noexcept;
    NAngle(NAngle&& other) noexcept;

    NAngle& operator=(const NAngle& other) noexcept;
    NAngle& operator=(NAngle&& other) noexcept;

    std::pair<double, double> GetCenter() const noexcept override;

    explicit operator double() const noexcept override;

    friend std::ostream& operator<< <N>(std::ostream& out, const NAngle<N>& f);
    friend std::istream& operator>> <N>(std::istream& in, NAngle<N>& f);

    ~NAngle() override = default;

private:
    Point center_;
    double phi_;
    double side_;
};
