#include <gtest/gtest.h>

#include <ostream>
#include "s21_set.h"
#include <set>
TEST(set_capacity, empty_set_00) {
  s21::set<int> s;
  ASSERT_EQ(s.empty(), true);
  ASSERT_EQ(s.size(), 0);
}
TEST(set_capacity, size_00) {
  s21::set<int> ms;
  std::set<int> sms;
  ASSERT_EQ(ms.max_size(), sms.max_size());
}

TEST(set_main, size_01) {
  s21::set<int> s1({{1}, {2}});
  ASSERT_EQ(s1.size(), 2);
}

TEST(set_iter, Iterators_00) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  std::set<int> s2({1, 3, 5, 6, 7, 99});

  s21::set<int>::iterator init = s1.begin();
  s21::set<int>::iterator end = s1.end();

  std::set<int>::iterator init_ = s2.begin();
  for (; init != end; ++init, ++init_) {
    ASSERT_EQ(*init, *init_);
  }
}

TEST(set_mod, remove_00) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s21::set<int>::iterator it = s1.begin();
  s1.erase(++it);
  it = s1.begin();
  ASSERT_EQ((*++it), 5);
}

TEST(set_mod, remove_01) {
  s21::set<int> s1{1, 8, 3, 5, 6, 11, 13, 14, 2, 4};
  s21::set<int>::iterator it = s1.find(8);
  s1.erase(it);
  EXPECT_EQ(s1.contains(8), false);
  EXPECT_EQ(s1.size(), 9);
  it = s1.find(5);
  s1.erase(it);
  EXPECT_EQ(s1.contains(5), false);
  EXPECT_EQ(s1.size(), 8);
}

TEST(set_mod, clean_00) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s1.clear();
  ASSERT_EQ(s1.empty(), true);
}

TEST(set_mod, merge_00) {
  s21::set<int> s1({3, 5, 6, 7});
  s21::set<int> s2({14, 21});
  s1.merge(s2);
  s21::set<int>::iterator it = s1.begin();
  ASSERT_EQ((*it), 3);
}

TEST(set_mod, swap_00) {
  s21::set<int> s1({21, 42, 33, 51});
  s21::set<int> s2({999, 45});
  s1.swap(s2);
  s21::set<int>::iterator it = s1.begin();
  ASSERT_EQ((*it), 45);
}

TEST(set_main, move_00) {
  s21::set<std::string> s1{"one", "two", "three"};
  s21::set<std::string> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.contains("one"), true);
  s21::set<std::string> s3{"1", "2"};
  s3 = std::move(s1);
  EXPECT_EQ(s3.size(), 0);
  EXPECT_EQ(s3.contains("2"), false);
}

TEST(set_main, copy_00) {
  s21::set<int> s1{1, 1, 2, 3, 5, 8};
  s21::set<int> s2 = s1;
  s2 = s2;
  EXPECT_EQ(s2.contains(5), true);
}

TEST(set_access, find_00) {
  s21::set<int> s1{1, 1, 2, 3, 5, 8};
  auto it = s1.find(3);
  EXPECT_EQ(*it, 3);
}

TEST(set_iter, Iterators_01) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s21::set<int>::const_iterator it = s1.cbegin();
  s21::set<int>::const_iterator it_ = s1.cbegin();
  EXPECT_EQ((it == it_), true);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ((it != it_), true);
}

TEST(set_mod, insert_02) {
  s21::set<int> s1{1, 8, 3};
  s1.insert_many(5, 6, 99);
  EXPECT_EQ(s1.contains(5), true);
  EXPECT_EQ(s1.contains(6), true);
  EXPECT_EQ(s1.contains(99), true);
}