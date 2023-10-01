#ifndef S21_CONTAINERS_MAP_H
#define S21_CONTAINERS_MAP_H

#include "s21_binary_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  struct mapCompare {
    bool operator()(const value_type& a, const value_type& b) const noexcept {
      return a.first < b.first;
    }
  };

  using iterator =
      typename BinaryTree<key_type, value_type, mapCompare>::iterator;
  using const_iterator =
      typename BinaryTree<key_type, value_type, mapCompare>::const_iterator;
  using Node = typename BinaryTree<key_type, value_type, mapCompare>::Node;

  map() : tree(new BinaryTree<key_type, value_type, mapCompare>) {}

  map(std::initializer_list<value_type> const& items)
      : tree(new BinaryTree<key_type, value_type, mapCompare>()) {
    for (auto item : items) {
      insert(item);
    }
  }

  map(const map& m) : tree(new BinaryTree<key_type, value_type, mapCompare>(*m.tree)) {}

  map(map&& m) : tree(new BinaryTree<key_type, value_type, mapCompare>(std::move(*m.tree))) {}

  map& operator=(map& m) {
    *tree = *m.tree;
    return *this;
  }

  map& operator=(map&& m) {
    clear();
    *tree = std::move(*m.tree);
    return *this;
  }

  ~map() {
    delete tree;
    tree = nullptr;
  }

  T& at(const Key& key) { return (*tree->at(key)).second; }

  T& operator[](const Key& key) { return at(key); }

  iterator begin() { return iterator(tree->minNode(), tree->getRoot()); }

  iterator end() { return iterator(nullptr, tree->getRoot()); }

  const_iterator cbegin() const noexcept {
    return const_iterator(tree->minNode(), tree->getRoot());
  }

  const_iterator cend() const noexcept {
    return const_iterator(nullptr, tree->getRoot());
  }

  bool empty() { return tree->empty(); }

  size_type size() { return tree->size(); }

  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / 2) / sizeof(Node);
  }

  std::pair<iterator, bool> insert(const reference value) {
    return tree->insertUnique(value);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return tree->insertUnique(value_type{key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type value = std::make_pair(key, obj);
    std::pair<iterator, bool> result = insert(value);
    if (result.second == false) {
      (*(result.first)).second = obj;
    }
    return result;
  }

  void erase(iterator pos) { tree->erase(pos); }

  void swap(map& other) { std::swap(tree, other.tree); }

  void clear() { tree->clearTree(); }

  void merge(map& other) {
    auto otherEnd = other.end();
    for (auto it = other.begin(); it != otherEnd; ++it) {
      insert(*it);
    }
    other.clear();
  }

  bool contains(const Key& key) { return tree->containsPair(key); }

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
  BinaryTree<key_type, value_type, mapCompare>* tree;
};

}  // namespace s21

#endif  // S21_CONTAINERS_MAP_H