#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() : size_(0), capacity_(0), data_(nullptr){};
  vector(int size, value_type data) : size_(size), capacity_(2 * size) {
    Allocate();
  };

  vector(const vector<value_type> &v) : size_(v.size_), capacity_(2 * v.size_) {
    Allocate();
    Copy(v);
  };

  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()), capacity_(2 * items.size()) {
    Allocate();
    auto it = items.begin();
    for (size_type i = 0; i < size_ && it != items.end(); i++, it++) {
      data_[i] = *it;
    }
  };

  vector(size_type n) : size_(n), capacity_(2 * n) { Allocate(); };

  vector(vector<value_type> &&v)
      : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  };

  ~vector() { Destruct(); }

  void operator=(vector<value_type> &&v) {
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  };

  reference at(size_type pos) {
    if (pos >= size_ || pos < 0) {
      throw std::out_of_range("pos > size or pos < 0");
    }
    return data_[pos];
  };

  reference operator[](size_type pos) { return data_[pos]; };

  const_reference front() {
    if (!data_) {
      throw std::invalid_argument("empty vector");
    }
    return data_[0];
  };

  const_reference back() {
    if (!data_) {
      throw std::invalid_argument("empty vector");
    }
    return data_[size_ - 1];
  };

  value_type *data() { return data_; };

  iterator begin() { return data_; };

  iterator end() { return data_ + size_; };

  bool empty() { return size_ == 0; };

  size_type size() { return size_; };

  size_type max_size() {
    return std::numeric_limits<value_type()>::std::max(value_type());
  };

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::out_of_range("size > max_size");
    }

    if (size > capacity) {
      value_type *temp;
      temp = new value_type[size];
      for (size_type i = 0; i < size_; i++) {
        temp[i] = data_[i];
      }
      delete data_;
      data_ = temp;
      capacity_ = size;
    }
  }

  size_type capacity() { return capacity_; };

  void shrink_to_fit() {
    value_type *p = end();
    delete p;
    capacity_ = size_;
  };

  void clear() {
    for (size_type i = 0; i < size_; i++) {
      data_[i] = value_type();
    }
  };

  iterator insert(iterator pos, const_reference value) {
    if (!pos) {
      throw std::logic_error("pos is null ptr");
    }
    value_type *temp = new value_type[capacity_ + 1];
    size_++;
    for (size_type i = 0; i < capacity_ + 1; i++) {
      temp[i] = value_type();
    }

    size_type counter = 0;
    const_iterator it = begin();
    while (it != pos && it) {
      temp[counter] = *it;
      counter++;
      it++;
    }

    temp[counter] = value;
    counter++;

    while (it && counter < size_) {
      temp[counter] = *it;
      counter++;
      it++;
    }
    delete[] data_;
    data_ = temp;
    return pos;
  };

  void erase(iterator pos) {
    value_type *temp = new value_type[capacity_]{};
    iterator it = data_;
    size_type i = 0;
    for (it; it != pos; i++, it++) {
      temp[i] = data_[i];
    }
    i++;
    for (i; i < size_; i++) {
      temp[i - 1] = data_[i];
    }
    delete[] data_;
    data_ = temp;
    size_ -= 1;
  }

  void push_back(const_reference value) {
    if (capacity_ == size_) {
      capacity_ *= 2;
    }
    value_type *temp = new value_type[capacity_]{};
    for (size_type i = 0; i < size_; i++) {
      temp[i] = data_[i];
    }
    temp[size_] = value;
    size_++;
    delete[] data_;
    data_ = temp;
  };

  void pop_back() {
    if (data_) {
      data_[size_] = value_type();
      size_--;
    }
  };

  void swap(vector &other) {
    value_type *temp_data = data_;
    size_type temp_size = size_;
    size_type temp_capacity = capacity_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = temp_data;
    other.size_ = temp_size;
    other.capacity_ = temp_capacity;
  }

 private:
  void Allocate() {
    try {
      data_ = new value_type[capacity_]{};
    } catch (std::bad_alloc()) {
      delete[] data_;
      throw new std::bad_alloc();
    }
  };

  void Destruct() { delete data_; };

  void Copy(const vector &v) {
    for (size_type i = 0; i < size_; i++) {
      data_[i] = v.data_[i];
    }
  };

  value_type *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // S21_VECTOR_H_