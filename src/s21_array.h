#ifndef S21_CONTAINERS_ARRAY_H
#define S21_CONTAINERS_ARRAY_H

#include  <exception>
#include <limits>

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  array() : size_(N) {}

  array(std::initializer_list<value_type> const& items) : size_(N) {
    std::copy(items.begin(), items.end(), arr_);
  }

  array(const array& a) : size_(a.size_) {
    std::copy(a.begin(), a.end(), arr_);
  }

  array(array&& a) : size_(a.size_) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = a.arr_[i];
    }
  }

  ~array() {}

  array<T, N>& operator=(array<T, N>&& a) noexcept {
    if (this != &a) {
      for (size_type i = 0; i < size_; ++i) {
        arr_[i] = a.arr_[i];
      }
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_)
      throw std::out_of_range("Error: position is out of bounds");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return *(arr_ + pos); }

  const_reference front() { return *arr_; }

  const_reference back() { return arr_[size_ - 1]; }

  iterator data() noexcept {
    if (size_ == 0)
      return nullptr;
    else
      return arr_;
  }

  iterator begin() { return iterator(arr_); }

  const_iterator begin() const { return const_iterator(arr_); }

  iterator end() { return arr_ + size_; }

  const_iterator end() const { return arr_ + size_; }

  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() { return size_; }

  void swap(array& other) {
    if (size() == other.size()) {
      value_type tmp;
      for (size_type i = 0; i < size_; i++) {
        tmp = arr_[i];
        arr_[i] = other.arr_[i];
        other.arr_[i] = tmp;
      }
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) arr_[i] = value;
  }

 private:
  size_type size_;
  value_type arr_[N] = {};
};
}  // namespace s21

#endif  // S21_CONTAINERS_ARRAY_H_
