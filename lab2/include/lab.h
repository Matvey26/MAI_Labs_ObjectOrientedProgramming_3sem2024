#pragma once
#include <string>
#include <iostream>

class Money {
public:
    // Конструкторы
    Money();
    explicit Money(const std::string& sum);
    explicit Money(double amount);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    ~Money();

    // Операции
    Money& operator=(const Money& other);
    Money& operator=(Money&& other) noexcept;

    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money operator*(const Money& other) const;
    Money operator/(const Money& other) const;
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(const Money& other);
    Money& operator/=(const Money& other);

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>=(const Money& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Money& money);

    // Другое
    std::string ToString(char sep = '.');

    void Swap(Money& other);

    size_t GetSize();
    unsigned char* GetDigits();

private:
    // Вспомогательные методы
    void parse_string(const std::string& sum);
    void normalize();
    void allocate_memory(size_t new_size);
    void deallocate_memory();

    // Поля класса
    unsigned char* digits_;
    size_t size_;
};