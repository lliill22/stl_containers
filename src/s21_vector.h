#ifndef S21_CONTAINERS_VECTOR_H_
#define S21_CONTAINERS_VECTOR_H_

#include <limits>
#include <exception>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n)
      : arr_(n ? new value_type[n]() : nullptr), size_(n), capacity_(n) {}

  vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = size_;
    arr_ = new value_type[capacity_];
    std::copy(items.begin(), items.end(), arr_);
  }

  vector(const vector &v) {
    if (this != &v) {
      size_ = v.size_;
      capacity_ = v.capacity_;
      if (size_ > 0) {
        arr_ = new value_type[capacity_];
        for (size_type i = 0; i < size_; i++) {
          arr_[i] = v.arr_[i];
        }
      }
    }
  }

  vector(vector &&v) {
    if (this != &v) {
      size_ = v.size_;
      capacity_ = v.capacity_;
      arr_ = v.arr_;
      v.arr_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
  }

  ~vector() {
    if (arr_ != nullptr && size_ > 0) {
      delete[] arr_;
    }
  }

  vector<value_type> &operator=(const vector<value_type> &v) {
    if (this != &v) {
      makeClean_();
      if (v.size_ > 0) {
        arr_ = new value_type[v.capacity_];
        for (size_type i = 0; i < v.size_; i++) {
          arr_[i] = v.arr_[i];
        }
        size_ = v.size_;
        capacity_ = v.capacity_;
      }
    }
    return *this;
  }

  vector<value_type> &operator=(vector<value_type> &&v) {
    delete[] arr_;
    arr_ = v.arr_;
    v.arr_ = nullptr;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.size_ = 0;
    v.capacity_ = 0;
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_)
      throw std::out_of_range("Error: position is out of bounds");
    return arr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_)
      throw std::out_of_range("Error: position is out of bounds");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }

  const_reference operator[](size_type pos) const { return at(pos); }

  const_reference front() const { return at(0); }

  const_reference back() const { return at(size_ - 1); }

  T *data() { return arr_; }

  const T *data() const { return arr_; }

  iterator begin() { return &at(0); }

  const_iterator begin() const { return &at(0); }

  iterator end() { return &at(size_ - 1); }

  const_iterator end() const { return &at(size_ - 1); }

  bool empty() const { return size_ == 0; }

  size_type size() const noexcept { return (size_); }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(size_type);
  }

  void reserve(size_type size) {
    if (size > max_size())
      throw std::length_error("Error: new_capsacity more than max_size");
    if (size > capacity_) {
      size_t temp_size = size_;
      value_type *arr = new value_type[size];
      for (size_type i = 0; i < temp_size; i++) arr[i] = arr_[i];
      makeClean_();
      arr_ = arr;
      size_ = temp_size;
      capacity_ = size;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ != size_) {
      size_t temp_size = size_;
      value_type *arr = new value_type[size_];
      for (size_type i = 0; i < size_; i++) arr[i] = arr_[i];
      makeClean_();
      arr_ = arr;
      size_ = temp_size;
      capacity_ = temp_size;
    }
  }

  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end())
      throw std::length_error(
          "Error: Accessing an inaccessible area of memory");
    if (pos == end()) {
      push_back(value);
      return arr_ + size() - 1;
    }
    auto new_pos = std::distance(begin(), pos);
    push_back(value_type());
    auto temp = arr_[new_pos];
    arr_[new_pos] = value;
    for (size_type i = new_pos + 1; i < size() - 1; i++)
      std::swap(temp, arr_[i]);
    arr_[size() - 1] = temp;
    return arr_ + new_pos;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos > end())
      throw std::length_error(
          "Error: Accessing an inaccessible area of memory");
    if (pos == begin()) {
      for (size_type i = 0; i < size_ - 1; i++) arr_[i] = arr_[i + 1];
    } else {
      size_type iter = 0;
      while ((begin() + iter) != pos) iter++;
      for (size_type i = iter + 1; i < size_ - 1; i++) arr_[i] = arr_[i + 1];
    }
    arr_[size_ - 1] = 0;
    size_--;
  }

  void push_back(const_reference value) {
    if (capacity_ == 0) reserve(1);
    if (size_ == capacity_) reserve(capacity_ * 2);
    arr_[size_] = value;
    size_++;
  }

  void pop_back() {
    if (size_ == 0) throw std::length_error("Error: vector is empty");
    size_--;
  }

  void swap(vector &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    if (pos < begin() || pos > end())
      throw std::length_error(
          "Error: Accessing an inaccessible area of memory");
    if (pos == end()) {
      insert_many_back(args...);
      return end() - 1;
    }
    vector<value_type> tmp{args...};
    iterator cur_pos = begin() + (pos - begin());
    for (size_type i = 0; i < tmp.size(); i++) {
      cur_pos = insert(cur_pos, tmp[i]);
      cur_pos++;
    }
    return cur_pos;
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    vector<value_type> tmp{args...};
    for (size_type i = 0; i < tmp.size(); i++) push_back(tmp[i]);
  }

 private:
  void makeClean_() {
    if (arr_ != nullptr) {
      delete[] arr_;
      size_ = 0;
      capacity_ = 0;
    }
  }

  value_type *arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_VECTOR_H_