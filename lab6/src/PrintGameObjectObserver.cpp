#include "../include/PrintGameObjectObserver.hpp"
#include <iostream>

PrintGameObjectObserver::PrintGameObjectObserver() {}

void PrintGameObjectObserver::Update(const std::string& message) {
    std::cout << message << std::endl;
}
