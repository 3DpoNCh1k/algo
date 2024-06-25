#include <algo/strings/suffix_array.hpp>
#include <iostream>

int main() {
    std::string s;
    std::cin >> s;
    auto suffix_array = algo::strings::SuffixArray(s);
    auto result = suffix_array.Solve();
    for(auto position: result) {
        std::cout << position << " ";
    }
    std::cout << std::endl;
}