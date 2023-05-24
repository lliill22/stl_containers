#include "s21_vector.h"
#include <vector>
int main () {
    s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
    s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};
    s21_vector_2.erase(s21_vector_2.end());
    for (int i = 0; i < s21_vector_2.size(); i++) {
        std::cout << s21_vector_1.at(i) << ' ' << s21_vector_2.at(i) << '\n';
    }
}
