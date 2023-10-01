#ifndef S21_CONTAINERS_SET_H
#define S21_CONTAINERS_SET_H

#include "s21_binary_tree.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  struct setCompare {
    bool operator()(const value_type& a, const value_type& b) const noexcept {
      return a < b;
    }
  };

  using iterator = typename BinaryTree<Key, Key, setCompare>::iterator;
  using const_iterator =
      typename BinaryTree<Key, Key, setCompare>::const_iterator;
  using Node = typename BinaryTree<Key, Key, setCompare>::Node;

  // default constructor, creates an empty set
  set() : tree(new BinaryTree<Key, Key, setCompare>) {}

  set(std::initializer_list<value_type> const& items)
      : tree(new BinaryTree<value_type, value_type, setCompare>()) {
    for (auto item : items) {
      insert(item);
    }
  }

  set(const set& s) : tree(new BinaryTree<value_type, value_type, setCompare>(*s.tree)) {}

  set(set&& s) : tree(new BinaryTree<value_type, value_type, setCompare>(std::move(*s.tree))) {}

  set& operator=(set& s) {
    *tree = *s.tree;
    return *this;
  }

  set& operator=(set&& s) {
    clear();
    *tree = std::move(*s.tree);
    return *this;
  }

  ~set() {
    delete tree;
    tree = nullptr;
  }

  bool empty() { return tree->empty(); }

  size_type size() { return tree->size(); }

  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / 2) / sizeof(Node);
  }

  iterator begin() { return iterator(tree->minNode(), tree->getRoot()); }

  iterator end() { return iterator(nullptr, tree->getRoot()); }

  const_iterator cbegin() const noexcept {
    return const_iterator(tree->minNode(), tree->getRoot());
  }

  const_iterator cend() const noexcept {
    return const_iterator(nullptr, tree->getRoot());
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree->insertUnique(value);
  }

  void erase(iterator pos) { tree->erase(pos); }
  void swap(set& other) { std::swap(tree, other.tree); }

  void clear() { tree->clearTree(); }

  void merge(set& other) {
    auto otherEnd = other.end();
    for (auto it = other.begin(); it != otherEnd; ++it) {
      insert(*it);
    }
    other.clear();
  }

  iterator find(const Key& key) { return tree->find(key); }

  bool contains(const Key& key) { return tree->contains(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    std::vector<value_type> arguments = {args...};
    for (auto& elem : arguments) {
      result.push_back(insert(elem));
    }
    return result;
  }

 private:
  BinaryTree<Key, Key, setCompare>* tree;
};

}  // namespace s21

#endif  // S21_CONTAINERS_SET_H