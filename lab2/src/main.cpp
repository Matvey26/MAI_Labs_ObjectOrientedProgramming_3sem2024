#include <iostream>
#include <cstring>
#include <stdexcept>
#include "../include/lab.h"

// Конструкторы и деструктор

Money::Money() : digits_(nullptr), size_(1) {
    allocate_memory(1);
    digits_[0] = 0;
}

Money::Money(const std::string& sum) : digits_(nullptr), size_(0) {
    parse_string(sum);
}

Money::Money(double amount) : digits_(nullptr), size_(0) {
    // Вычисляем необходимый размер буфера
    int len = std::snprintf(nullptr, 0, "%.2f", amount);
    char* buffer = new char[len + 1]; // +1 для нуль-терминатора
    std::snprintf(buffer, len + 1, "%.2f", amount); // Преобразуем double в строку
    parse_string(std::string(buffer));
    delete[] buffer;
}

Money::Money(const Money& other) : digits_(nullptr), size_(other.size_) {
    allocate_memory(size_);
    std::memcpy(digits_, other.digits_, size_);
}

Money::Money(Money&& other) noexcept : digits_(other.digits_), size_(other.size_) {
    other.digits_ = nullptr;
    other.size_ = 0;
}

Money::~Money() {
    deallocate_memory();
}

// Работа с памятью

void Money::allocate_memory(size_t new_size) {
    size_ = new_size;
    digits_ = new unsigned char[size_]{};
}

void Money::deallocate_memory() {
    delete[] digits_;
    digits_ = nullptr;
    size_ = 0;
}

// Метод парсинга строки
void Money::parse_string(const std::string& sum) {

    size_t len = sum.size();
    if (len < 4) {
        throw std::invalid_argument("Invalid string format. Need: <int><sep><two digits>");
    }
    deallocate_memory();
    allocate_memory(len - 1);

    for (size_t i = 0; i < size_; ++i) {
        size_t si = len - i - 1 - static_cast<int>(i > 1);
        if (sum[si] >= '0' && sum[si] <= '9') {
            digits_[i] = static_cast<unsigned char>(sum[si] - '0');
        } else {
            throw std::invalid_argument("Invalid character in money string.");
        }
    }

    // normalize();
}

// // Метод нормализации (обработка переполнения копеек)
// void Money::normalize() {
//     if (size_ > 2) {
//         unsigned carry = 0;
//         for (size_t i = 0; i < size_; ++i) {
//             unsigned value = digits_[i] + carry;
//             digits_[i] = value % 10;
//             carry = value / 10;
//         }
//     }
// }

// Операторы присваивания

Money& Money::operator=(const Money& other) {
    Money copy = other;
    Swap(copy);
    return *this;
}


Money& Money::operator=(Money&& other) noexcept {
    if (this != &other) {
        deallocate_memory();
        digits_ = other.digits_;
        size_ = other.size_;
        other.digits_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

// Числовые операции

Money Money::operator+(const Money& other) const {
    Money result(*this);
    result += other;
    return result;
}

Money Money::operator-(const Money& other) const {
    Money result(*this);
    result -= other;
    return result;
}

Money Money::operator*(const Money& other) const {
    Money result(*this);
    result *= other;
    return result;
}

Money Money::operator/(const Money& other) const {
    Money result(*this);
    result /= other;
    return result;
}

Money& Money::operator+=(const Money& other) {
    size_t max_size = std::max(size_, other.size_);
    unsigned char* new_digits = new unsigned char[max_size + 1]{};
    unsigned carry = 0;

    for (size_t i = 0; i < max_size; ++i) {
        unsigned value = (i < size_ ? digits_[i] : 0) + (i < other.size_ ? other.digits_[i] : 0) + carry;
        new_digits[i] = value % 10;
        carry = value / 10;
    }

    if (carry > 0) {
        new_digits[max_size] = carry;
        max_size++;
    }

    deallocate_memory();
    digits_ = new_digits;
    size_ = max_size + 1;
    
    return *this;
}

Money& Money::operator-=(const Money& other) {
    if (*this < other) {
        throw std::invalid_argument("Negative balance.");
    }
    size_t max_size = std::max(size_, other.size_);
    unsigned char* new_digits = new unsigned char[max_size]{};
    unsigned carry = 0;

    for (size_t i = 0; i < max_size; ++i) {
        unsigned value = 10 + (i < size_ ? digits_[i] : 0) - carry - (i < other.size_ ? other.digits_[i] : 0);
        new_digits[i] = value % 10;
        carry = 1 - value / 10;
    }

    deallocate_memory();
    digits_ = new_digits;
    size_ = max_size;
    
    return *this;
}

Money& Money::operator*=(const Money& other) {
    size_t max_size = size_ + other.size_;
    unsigned char* new_digits = new unsigned char[max_size - 1]{};
    unsigned carry = 0;

    for (size_t i = 0; i < other.size_; ++i) {
        carry = 0;
        for (size_t j = 0; j < size_; ++j) {
            unsigned value = digits_[j] * other.digits_[i] + carry;
            if (i + j >= 2) {
                new_digits[i + j - 2] += value % 10;
            }
            carry = value / 10;
        }
    }

    carry = 0;
    for (size_t i = 0; i < size_; ++i) {
        unsigned value = new_digits[i] + carry;
        new_digits[i] = value % 10;
        carry = value / 10;
    }

    deallocate_memory();
    digits_ = new_digits;
    size_ = max_size + 1;
    
    return *this;
}

Money& Money::operator/=(const Money& other) {
    if (other == Money("0")) {
        throw std::invalid_argument("Division by zero.");
    }

    return *this;
}

// Другие методы и операции

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Money& money) {
    size_t min_size = std::max(static_cast<size_t>(3), money.size_);
    for (size_t i = min_size; i > 0; --i) {
        os << static_cast<int>((i - 1 < money.size_ ? money.digits_[i - 1] : 0));
        if (i - 1 == 2) {
            os << '.';
        }
    }
    return os;
}

void Money::Swap(Money& other) {
    std::swap(digits_, other.digits_);
    std::swap(size_, other.size_);
}

size_t Money::GetSize() {
    return size_;
}

unsigned char* Money::GetDigits() {
    return digits_;
}

std::string Money::ToString(char sep) {
    std::string result(std::max(static_cast<size_t>(4), size_ + 1), ' ');
    result[result.size() - 3] = sep;

    for (size_t i = 0; i < result.size() - 1; ++i) {
        size_t si = result.size() - i - 1 - static_cast<int>(i > 1);
        result[si] = (i < size_ ? digits_[i] : 0) + '0';
    }

    return result;
}

// Операторы отношений и равенства

bool Money::operator==(const Money& other) const {
    size_t max_size = std::max(size_, other.size_);
    for (size_t i = 0; i < max_size; ++i) {       
        if ((i < size_ ? digits_[i] : 0) != (i < other.size_ ? other.digits_[i] : 0)) {
            return false;
        }
    }
    return true;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator>(const Money& other) const {
    size_t max_size = std::max(size_, other.size_);
    for (size_t i = max_size; i > 0; --i) {       
        unsigned char left_digit = (i - 1 < size_ ? digits_[i - 1] : 0);
        unsigned char right_digit = (i - 1 < other.size_ ? other.digits_[i - 1] : 0); 
        if (left_digit > right_digit) {
            return true;
        }
        if (left_digit < right_digit) {
            return false;
        }
    }
    return false;
}

bool Money::operator<(const Money& other) const {
    return other > *this;
}

bool Money::operator<=(const Money& other) const {
    return !(*this > other);
}

bool Money::operator>=(const Money& other) const {
    return !(*this < other);
}
