#include <iostream>
#include <string>
#include <memory_resource>
#include "include/Stack.hpp"
#include "include/MapDynamicMemoryResource.hpp"

struct ComplexType {
    int id;
    std::string name;
    double value;

    ComplexType(int id_, const std::string& name_, double value_)
        : id(id_), name(name_), value(value_) {}
};

void DemonstrateStack() {
    std::cout << "=== Stack with int ===" << std::endl;
    Stack<int> intStack;
    intStack.Push(10);
    intStack.Push(20);
    intStack.Push(30);

    std::cout << "Stack size: " << intStack.Size() << std::endl;
    while (!intStack.Empty()) {
        std::cout << "Top: " << intStack.Top() << std::endl;
        intStack.Pop();
    }

    std::cout << "\n=== Stack with ComplexType ===" << std::endl;
    Stack<ComplexType> complexStack;
    complexStack.Emplace(1, "First", 100.0);
    complexStack.Emplace(2, "Second", 200.5);
    complexStack.Emplace(3, "Third", 300.75);

    std::cout << "Stack size: " << complexStack.Size() << std::endl;
    while (!complexStack.Empty()) {
        const ComplexType& top = complexStack.Top();
        std::cout << "Top: { id: " << top.id 
                  << ", name: " << top.name 
                  << ", value: " << top.value << " }" << std::endl;
        complexStack.Pop();
    }

    std::cout << "\n=== Stack with custom allocator ===" << std::endl;
    MapDynamicMemoryResource memoryResource;
    std::pmr::polymorphic_allocator<int> allocator(&memoryResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> allocStack(allocator);

    allocStack.Push(100);
    allocStack.Push(200);
    allocStack.Push(300);

    std::cout << "Stack size (with custom allocator): " << allocStack.Size() << std::endl;
    while (!allocStack.Empty()) {
        std::cout << "Top: " << allocStack.Top() << std::endl;
        allocStack.Pop();
    }

    std::cout << "Allocator used blocks: " << memoryResource.get_used_blocks_count() << std::endl;
    std::cout << "Allocator free blocks: " << memoryResource.get_free_blocks_count() << std::endl;
}

int main() {
    DemonstrateStack();
    return 0;
}
