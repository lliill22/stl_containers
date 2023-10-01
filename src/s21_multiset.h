#ifndef S21_CONTAINERS_MULTISET_H
#define S21_CONTAINERS_MULTISET_H

#include "s21_binary_tree.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  struct multisetCompare {
    bool operator()(const value_type& a, const value_type& b) const noexcept {
      return a < b;
    }
  };

  using iterator =
      typename BinaryTree<key_type, value_type, multisetCompare>::iterator;
  using const_iterator = typename BinaryTree<key_type, value_type,
                                             multisetCompare>::const_iterator;
  using Node = typename BinaryTree<key_type, value_type, multisetCompare>::Node;

  multiset() : tree(new BinaryTree<key_type, value_type, multisetCompare>) {}

  multiset(std::initializer_list<value_type> const& items)
      : tree(new BinaryTree<value_type, value_type, multisetCompare>()) {
    for (auto item : items) {
      insert(item);
    }
  }

  multiset(const multiset& ms) : tree(new BinaryTree<value_type, value_type, multisetCompare>(*ms.tree)) {}

  multiset(multiset&& ms) : tree(new BinaryTree<value_type, value_type, multisetCompare>(std::move(*ms.tree))) {}

  multiset& operator=(multiset& ms) {
    *tree = *ms.tree;
    return *this;
  }

  multiset& operator=(multiset&& ms) {
    clear();
    *tree = std::move(*ms.tree);
    return *this;
  }

  ~multiset() {
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

  iterator insert(const value_type& value) {
    std::pair<iterator, bool> getIter = tree->insertNonUnique(value);
    return getIter.first;
  }

  void erase(iterator pos) { tree->erase(pos); }

  bool contains(const Key& key) { return tree->contains(key); }

  void swap(multiset& other) { std::swap(tree, other.tree); }

  void clear() { tree->clearTree(); }

  void merge(multiset& other) {
    auto otherEnd = other.end();
    for (auto it = other.begin(); it != otherEnd; ++it) {
      insert(*it);
    }
    other.clear();
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const Key& key) { return tree->findLowerBound(key); }

  iterator upper_bound(const Key& key) { return tree->findUpperBound(key); }

  iterator find(const Key& key) { return tree->find(key); }

  size_type count(const Key& key) { return tree->count(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    std::vector<value_type> arguments = {args...};
    for (auto& elem : arguments) {
      result.push_back(tree->insertNonUnique(elem));
    }
    return result;
  }

 private:
  BinaryTree<Key, Key, multisetCompare>* tree;
};

}  // namespace s21

#endif  // S21_CONTAINERS_MULTISET_H