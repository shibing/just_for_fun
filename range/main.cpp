#include "range.hpp"

#include <iostream>

int main() {
    for (auto x : shibing::range(10)) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    for (auto x : shibing::range(1, 10, 2)) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    for (auto x : shibing::range(10, -1, -1)) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    for (auto x : shibing::range(1.0, 100.0, 2.1)) {
        std::cout << x << " ";
    }

    std::cout << "\n";

    for (auto x : shibing::range(10.0, 1.0, -1.1)) {
        std::cout << x << " ";
    }
    return 0;
}
