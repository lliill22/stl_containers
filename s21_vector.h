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
  }


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

  void operator=(vector<value_type> v) : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

 private:
  void Allocate(value_type data) {
    try {
      data_ = new value_type[capacity_]{data};
    } catch (bad_alloc) {
      delete[] data;
      throw new bad_alloc;
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