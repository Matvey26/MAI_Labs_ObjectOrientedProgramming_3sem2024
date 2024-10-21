#pragma once
#include "Point.hpp"
#include <initializer_list>
#include <utility>
#include <iostream>

class Figure {
public:
    // Конструкторы и деструктор
    Figure() noexcept;
    Figure(size_t vertices_number, Point* points) noexcept;
    Figure(std::initializer_list<std::pair<double, double>> points) noexcept;
    Figure(const Figure& other) noexcept;
    Figure(Figure&& other) noexcept;
    ~Figure() noexcept;

    // Геттеры
    std::pair<double, double> GetCenter() const noexcept;
    size_t GetVerticesNumber() const noexcept;
    Point* GetVertices() noexcept;

    // Операторы
    explicit operator double() const noexcept;
    Figure& operator=(const Figure& other);

    friend std::ostream& operator<<(std::ostream& out, const Figure& f);
    friend std::istream& operator>>(std::istream& in, Figure& f);

private:
    size_t vertices_number_;
    Point* points_;
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Figure& f);
std::istream& operator>>(std::istream& in, Figure& f);