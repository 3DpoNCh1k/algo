#include <algo/strings/z_function.hpp>
#include <iostream>

int main() {
    std::string s;
    std::cin >> s;
    auto lcps = algo::strings::ZFunction(s);
    for(auto l: lcps) {
        std::cout << l << " ";
    }
    std::cout << std::endl;
}