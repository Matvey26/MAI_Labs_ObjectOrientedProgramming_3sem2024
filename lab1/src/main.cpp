#include "../include/lab.h"
#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>

double feet_to_inch(double feet_value) {
    static const double FEET_TO_INCH = 12.;
    return FEET_TO_INCH * feet_value;
}

uint64_t safe_multiply(uint64_t a, uint64_t b) {
    if (a == 0 || b == 0) return 0;
    if (a > UINT64_MAX / b) {
        throw std::overflow_error("Multiplication overflow");
    }
    return a * b;
}

uint64_t box_capacity(double length, double width, double height) {
    static const uint64_t BOX_SIZE = 16;

    uint64_t length_boxes = feet_to_inch(length) / BOX_SIZE;
    uint64_t width_boxes = feet_to_inch(width) / BOX_SIZE;
    uint64_t height_boxes = feet_to_inch(height) / BOX_SIZE;
    
    uint64_t result = length_boxes;
    std::cout << result << '\n';
    try {
        result = safe_multiply(result, width_boxes);
        std::cout << result << '\n';
        result = safe_multiply(result, height_boxes);
        std::cout << result << '\n';
    } catch (const std::overflow_error&) {
        return UINT64_MAX;
    }
    return result;
}