using namespace std;
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

  vector() : size_(0), capacity_(0) data_(nullptr){};
  vector(int size, value_type data) : size_(size), capacity_(2 * size){Allocate()};

  vector(const vector<value_type> &v) : size_(v.size_), capacity_(2 * v.size_) {
    Allocate(v);
    Copy(v);
  };

  vector(std::initializer_list<value_type> const &items) : size_(item.size()), capacity_(2 * item.size()) {
    Allocate(value_type());
    std::copy(items.begin(), items.end(), data);
  };


  vector(size_type n) : size_(n), capacity_(2 * n) {
    Allocate(value_type());
  };

  vector(vector<value_type> &&v) : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  };

  ~vector() {
    Destruct();
  }

  void operator=(vector<value_type> &&v) : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  };

  reference at(size_type pos) {
    if (pos => size_ || pos < 0) {
      throw std::out_of_range("pos > size or pos < 0")
    }
    return data_[pos]
  };

  reference operator[] (size_type pos) {
    return data_[pos];
  };

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

  value_type* data() {
    return data_;
  };

  iterator begin() {
    return data_;
  };

  iterator end() {
    return data_+size_;
  };

  bool empty() {
    return data_ ? true : false;
  };
  
  size_type size() {
    return size_;
  };

  size_type max_size() {
    return std::numeric_limits<value_type>::max();
  };

  void reserve (size_type size) {
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

  size_type capacity() {
    return capacity_;
  };

  void shrink_to_fit() {
    value_type* p = end();
    delete p;
    capacity_ = size_;
  };

  void clear() {
    for (size_type i = 0; i < size_; i++) {
      data_[i] = value_type();
    }
  };

  // iterator insert(iterator pos, const_reference value) {

  // };

  // void erase(iterator pos) {

  // }

  void push_back(const_reference value) {
    if (capacity_ <= size_) {
      value_type *temp = new value_type[size_*2];
      for (size_type i = 0; i < size_; i++) {
        temp[i] = data_[i];
      }
      size_++;
      temp[size_] = value;
      delete data_;
      data_ = temp;
      capacity_ = size_ * 2;
    } else {
      data_[size_+1] = value;
    }
  };

  void pop_back() {
    if (data_) {
      data_[size_] = value_type();
      size_--;
    }
  };
  
  void swap(vector& other) {
    value_type *temp = other.data_;
    other.data_ = data_;
    data_ = temp;
  }
  
 private:
  void Allocate(value_type data) {
    try {
      data_ = new value_type[capacity_]{data};
    } catch (bad_alloc) {
      delete[] data;
      throw new std::bad_alloc();
    }
  };

  void Destruct() {
    delete data_;
  };

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