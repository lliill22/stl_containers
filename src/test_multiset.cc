#include <gtest/gtest.h>

#include <ostream>

#include "s21_multiset.h"

TEST(multiset_capacity, empty_multiset_00) {
  s21::multiset<int> ms;
  ASSERT_EQ(ms.empty(), true);
  ASSERT_EQ(ms.size(), 0);
}
TEST(multiset_capacity, size_00) {
  s21::multiset<int> ms;
  std::multiset<int> sms;
  ASSERT_EQ(ms.max_size(), sms.max_size());
}

TEST(multiset_main, size_01) {
  s21::multiset<int> ms1({{1}, {2}});
  ASSERT_EQ(ms1.size(), 2);
}

TEST(multiset_iter, Iterators_00) {
  s21::multiset<int> ms1({1, 3, 5, 6});
  s21::multiset<int>::iterator it = ms1.begin();
  ASSERT_EQ((*it), 1);
  ++it;
  ++it;
  ASSERT_EQ((*--it), 3);
}

TEST(multiset_mod, remove_00) {
  s21::multiset<int> ms1({1, 3, 5, 6, 7, 99});
  s21::multiset<int>::iterator it = ms1.begin();
  ms1.erase(++it);
  it = ms1.begin();
  ASSERT_EQ((*++it), 5);
}

TEST(multiset_mod, clean_00) {
  s21::multiset<int> ms1({1, 3, 5, 6, 7, 99});
  ms1.clear();
  ASSERT_EQ(ms1.empty(), true);
}
TEST(multiset_mod, insert_00) {
  s21::multiset<int> ms1;
  s21::multiset<int>::iterator it = ms1.insert(35);
  ASSERT_EQ((*it), 35);
}

TEST(multiset_mod, merge_00) {
  s21::multiset<int> ms1({3, 5, 6, 7});
  s21::multiset<int> ms2({14, 21});
  ms1.merge(ms2);
  s21::multiset<int>::iterator it = ms1.begin();
  ASSERT_EQ((*it), 3);
}

TEST(multiset_access, bounds_00) {
  s21::multiset<int> ms{1, 3, 7, 23, 55};
  std::multiset<int> std_ms{1, 3, 7, 23, 55};
  auto it = ms.equal_range(7);
  auto std_it = std_ms.equal_range(7);
  ASSERT_EQ(*(it).first, *(std_it).first);
  ASSERT_EQ(*(it).second, *(std_it).second);
}

TEST(multiset_access, find_00) {
  s21::multiset<int> ms{1, 3, 7, 23, 55};
  auto it = ms.find(23);
  ASSERT_EQ(*(it), 23);
}

TEST(multiset_mod, swap_00) {
  s21::multiset<int> ms1({21, 33, 51});
  s21::multiset<int> ms2({999, 45});
  ms1.swap(ms2);
  s21::multiset<int>::iterator it = ms1.begin();
  ASSERT_EQ((*it), 45);
}

TEST(multiset_access, count_00) {
  s21::multiset<int> ms{1, 3, 3, 7, 23, 3};
  int count = ms.count(3);
  ASSERT_EQ(count, 3);
}

TEST(multiset_main, move_00) {
  s21::multiset<std::string> ms1{"one", "two", "three"};
  s21::multiset<std::string> ms2(std::move(ms1));
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms2.contains("one"), true);
  s21::multiset<std::string> ms3{"1", "2"};
  ms3 = std::move(ms1);
  EXPECT_EQ(ms3.size(), 0);
  EXPECT_EQ(ms3.contains("2"), false);
}

TEST(multiset_main, copy_00) {
  s21::multiset<int> ms1{1, 1, 2, 3, 5, 8};
  s21::multiset<int> ms2 = ms1;
  ms2 = ms2;
  EXPECT_EQ(ms2.contains(5), true);
}

TEST(multiset_mod, insert_02) {
  s21::multiset<int> ms1{1, 8, 3};
  ms1.insert_many(5, 6, 99);
  EXPECT_EQ(ms1.contains(5), true);
  EXPECT_EQ(ms1.contains(6), true);
  EXPECT_EQ(ms1.contains(99), true);
}