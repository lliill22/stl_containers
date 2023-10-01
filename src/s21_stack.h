#ifndef S21_STACK_H
#define S21_STACK_H
#include "s21_vector.h"

namespace s21 {
template <class T, class Container = s21::vector<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 public:
  stack() : cont() {}
  stack(std::initializer_list<value_type> const &items) : cont(items) {}
  stack(const stack &s) : cont(s.cont) {}
  stack(stack &&s) : cont(std::move(s.cont)) {}
  ~stack() {}
  stack &operator=(stack &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }

  const_reference top() { return cont.back(); }
  void clear() { return cont.clear(); }
  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }
  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_back(); }
  void swap(stack &other) { this->cont.swap(other.cont); }
  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push(elem);
    }
  }

 private:
  Container cont;
};

}  //  namespace s21

#endif  // S21_STACK_H