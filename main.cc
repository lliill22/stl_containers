#include <vector>
#include "s21_vector.h"

#include <iostream>

int main() {
    s21::vector<int> s21_vector = {1, 2, 3, 4};
    std::vector<int> std_vector = {1, 2, 3, 4};
    std::cout << (s21_vector.front() == std_vector.front()) << '\n';
    std::cout << (s21_vector.back() == std_vector.back()) << '\n';
    std::cout << (s21_vector.size(), std_vector.size()) << '\n';
    std::cout << (s21_vector.empty(), std_vector.empty());
}