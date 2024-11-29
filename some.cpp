#include <iostream>
#include <set>
#include <memory>

struct A {
    int a;
};

int main() {
    auto a1 = std::make_shared<A>(A{5});
    auto a2 = std::make_shared<A>(A{2});
    auto a3 = std::make_shared<A>(A{10});

    std::set<std::shared_ptr<A>> s;
    s.insert(a1);
    s.insert(a2);
    s.insert(a3);
    s.insert(a1);  // Не вставится, так как элемент уже есть в set

    for (auto i : s) {
        std::cout << i->a << ' ';
    }
    std::cout << '\n';
}
