#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <utility>

#include "cstdio"

namespace s21 {
template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node_ {
    value_type value_ = T();
    Node_ *prev_ = nullptr;
    Node_ *next_ = nullptr;
    Node_() = default;
    Node_(value_type value) : value_(value), prev_(nullptr), next_(nullptr) {}
  };
  Node_ *head_ = nullptr;
  Node_ *tail_ = nullptr;
  Node_ *end_ = nullptr;
  size_type size_ = 0;

  class ListConstIterator {
   public:
    ListConstIterator() noexcept { cursor = nullptr; }
    explicit ListConstIterator(Node_ *ptr) : cursor(ptr){};
    ListConstIterator(const ListConstIterator &other) noexcept
        : cursor(other.cursor){};
    ~ListConstIterator() = default;
    const_reference operator*() const { return cursor->value_; }
    ListConstIterator &operator++() {
      if (cursor->next_ != nullptr) {
        cursor = cursor->next_;
      }
      return *this;
    }
    ListConstIterator &operator++(int) {
      if (cursor->next_ != nullptr) {
        cursor = cursor->next_;
      }
      return *this;
    }
    ListConstIterator &operator--(int) {
      if (cursor->prev_ != nullptr) {
        cursor = cursor->prev_;
      }
      return *this;
    }
    ListConstIterator &operator--() {
      if (cursor->prev_ != nullptr) {
        cursor = cursor->prev_;
      }
      return *this;
    }

    bool operator==(ListConstIterator other) { return cursor == other.cursor; }
    bool operator!=(ListConstIterator other) { return cursor != other.cursor; }
    Node_ *cursor = nullptr;
  };

  class ListIterator : public ListConstIterator {
   public:
    ListIterator() : ListConstIterator() {}
    ListIterator(Node_ *ptr) : ListConstIterator(ptr) {}
    ListIterator(const ListIterator &other) : ListConstIterator(other) {}
    value_type &operator*() { return this->cursor->value_; }
    ~ListIterator() = default;
    ListIterator operator-(const size_type value) {
      Node_ *tmp = this->cursor;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->prev_;
      }
      ListIterator res(tmp);
      return res;
    }
  };

 public:
  list() {
    head_ = tail_ = nullptr;
    end_ = new Node_();
  };
  explicit list(size_type n) {
    end_ = new Node_();
    for (size_type i = 0; i < n; i++) {
      push_back(T());
    }
  }
  list(std::initializer_list<value_type> const &items)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    if (items.size() != 0) {
      end_ = new Node_();
      for (value_type n : items) {
        push_back(n);
      }
    }
  }
  list(const list &l)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node_();
    Node_ *current = l.head_;
    for (size_type i = 0; i != l.size_; i++) {
      push_back(current->value_);
      current = current->next_;
    }
  }
  list(list &&l) noexcept {
    head_ = std::exchange(l.head_, nullptr);
    tail_ = std::exchange(l.tail_, nullptr);
    end_ = std::exchange(l.end_, nullptr);
    size_ = std::exchange(l.size_, 0);
  }
  ~list() {
    if (!empty()) clear();
    delete end_;
  };
  list &operator=(list &&l) noexcept {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  size_type size() const noexcept { return size_; }

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() const { return !head_ ? iterator(end_) : iterator(head_); }
  iterator end() const { return iterator(end_); }
  const_reference front() {
    if (empty()) {
      return end_->value_;
    } else {
      return head_->value_;
    }
  }
  const_reference back() {
    if (empty()) {
      return end_->value_;
    } else {
      return tail_->value_;
    }
  }
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(Node_) / 2);
  }

  bool empty() const noexcept { return size_ == 0; }

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }

  void pop_front() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    } else {
      if (head_ != tail_) {
        auto *tmp = head_;
        head_ = head_->next_;
        delete tmp;
      } else {
        delete head_;
        head_ = nullptr;
      }
      size_--;
      end_->value_ = size_;
    }
  }

  void pop_back() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    } else {
      if (head_ != tail_) {
        auto *tmp = tail_;
        tail_ = tail_->prev_;
        delete tmp;
      } else {
        delete head_;
        head_ = nullptr;
      }
      size_--;
      end_->value_ = size_;
    }
  }

  void push_front(const_reference value) {
    Node_ *new_node_ = new Node_(value);
    if (empty()) {
      head_ = new_node_;
      tail_ = new_node_;
      head_->next_ = end_;
      head_->prev_ = end_;
    } else {
      new_node_->next_ = head_;
      head_->prev_ = new_node_;
      head_ = new_node_;
      head_->prev_ = end_;
      end_->prev_ = tail_;
      end_->next_ = head_;
    }
    size_++;
    end_->value_ = size_;
  }

  void push_back(const_reference value) {
    Node_ *new_node_ = new Node_(value);
    if (empty()) {
      head_ = new_node_;
      tail_ = new_node_;
      head_->next_ = end_;
      head_->prev_ = end_;
    } else {
      tail_->next_ = new_node_;
      new_node_->prev_ = tail_;
      tail_ = new_node_;
      tail_->next_ = end_;
      end_->prev_ = tail_;
      end_->next_ = head_;
    }
    size_++;
    end_->value_ = size_;
  }

  void swap(list &other) {
    using std::swap;
    swap(this->head_, other.head_);
    swap(this->tail_, other.tail_);
    swap(this->size_, other.size_);
    swap(this->end_, other.end_);
  }

  iterator insert(iterator pos, const_reference value) {
    Node_ *current = pos.cursor;
    if (empty()) {
      push_back(value);
      end_->value_ = size_;
      return iterator(head_);
    } else if (current == head_) {
      push_front(value);
      end_->value_ = size_;
      return iterator(head_);
    } else if (current == end_) {
      push_back(value);
      end_->value_ = size_;
      return iterator(tail_);
    } else {
      Node_ *add = new Node_(value);
      add->next_ = current;
      add->prev_ = current->prev_;
      current->prev_->next_ = add;
      current->prev_ = add;
      size_++;
      end_->value_ = size_;
      return iterator(add);
    }
  }

  void erase(iterator pos) {
    if (pos.cursor == nullptr || pos.cursor == end_) {
      throw std::logic_error("Invalid position");
    }
    if (pos.cursor == head_) {
      pop_front();
      end_->value_ = size_;
      if (size_ == 0) {
        head_ = nullptr;
      }
    } else if (pos.cursor == tail_) {
      pop_back();
      end_->value_ = size_;
    } else {
      pos.cursor->prev_->next_ = pos.cursor->next_;
      pos.cursor->next_->prev_ = pos.cursor->prev_;
      delete pos.cursor;
      size_--;
      end_->value_ = size_;
    }
  }

  void splice(const_iterator pos, list &other) {
    iterator tempIterator = iterator(pos.cursor);
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end(); ++it) {
        this->insert(tempIterator, *it);
      }
      other.clear();
    }
  }

  void reverse() {
    if (!empty() && size_ != 1) {
      std::swap(tail_, head_);
      std::swap(end_->prev_, end_->next_);
      auto iter = begin();
      while (iter.cursor != end_) {
        std::swap(iter.cursor->next_, iter.cursor->prev_);
        ++iter;
      }
    }
  }

  void unique() {
    if (!this->empty()) {
      for (iterator it = this->begin(); it != this->end(); it++) {
        if (it.cursor->value_ == it.cursor->prev_->value_) {
          iterator del_it = (it - 1);
          this->erase(del_it);
        }
      }
    }
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push_back(elem);
    }
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push_front(elem);
    }
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator iter = iterator(pos.cursor);
    for (auto elem : {std::forward<Args>(args)...}) {
      insert(iter, elem);
    }
    --iter;
    return iter;
  }

  void merge(list &other) {
    if (!this->empty() && !other.empty()) {
      iterator iter_this = this->begin();
      iterator iter_other = other.begin();
      while (iter_this != this->end()) {
        if (iter_other != other.end()) {
          if (iter_this.cursor->value_ >= iter_other.cursor->value_) {
            this->insert(iter_this, iter_other.cursor->value_);
            iter_other++;
          } else {
            iter_this++;
          }
        } else {
          break;
        }
      }
      while (iter_other != other.end()) {
        this->insert(iter_this, iter_other.cursor->value_);
        iter_other++;
      }
    } else if (this->empty() && !other.empty()) {
      Node_ *current = other.head_;
      for (size_type i = 0; i != other.size_; i++) {
        push_back(current->value_);
        current = current->next_;
      }
    }
    other.clear();
  }

  void sort() {
    if (!empty()) {
      iterator first = this->begin();
      iterator last = this->end();
      --last;
      quick_sort(first, last);
    }
  }

 private:
  iterator partition(iterator first, iterator last) {
    value_type pivot_value = last.cursor->value_;
    iterator it = first;

    for (iterator k = first; k != last; ++k) {
      if (k.cursor->value_ <= pivot_value) {
        std::swap(it.cursor->value_, k.cursor->value_);
        it++;
      }
    }
    std::swap(it.cursor->value_, last.cursor->value_);
    return it;
  }

  void quick_sort(iterator first, iterator last) {
    if (first == last || first.cursor == end_ || last.cursor == end_ ||
        first.cursor == tail_)
      return;
    iterator pivot = partition(first, last);
    --pivot;
    quick_sort(first, pivot);
    ++pivot;
    quick_sort(pivot, last);
  }
};

}  // namespace s21
#endif  // S21_LIST_H
