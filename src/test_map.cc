#include <gtest/gtest.h>

#include <ostream>

#include "s21_map.h"

TEST(map_capacity, empty_map_00) {
  s21::map<int, int> m1;
  ASSERT_EQ(m1.empty(), true);
  ASSERT_EQ(m1.size(), 0);
}

TEST(map_capacity, size_00) {
  s21::map<int, int> m1;
  std::map<int, int> smap;
  ASSERT_EQ(m1.max_size(), smap.max_size());
}

TEST(map_main, size_01) {
  s21::map<int, int> m1({{2, 42}, {4, 0}, {1, 21}, {3, 33}});
  ASSERT_EQ(m1.size(), 4);
}

TEST(map_iter, Iterators_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {5, 51}});
  s21::map<int, int>::iterator it = m1.begin();
  ASSERT_EQ((*it).first, 1);
  ASSERT_EQ((*++it).first, 2);
  ASSERT_EQ((*++it).first, 3);
  ASSERT_EQ((*++it).first, 5);
  s21::map<int, int>::iterator it0 = m1.end();
  ASSERT_EQ(++it == it0, true);
}

TEST(map_iter, Iterators_01) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {5, 51}});
  s21::map<int, int>::iterator it = m1.begin();
  s21::map<int, int>::iterator cit = m1.begin();
  ASSERT_EQ(it == cit, true);
  ++cit;
  ASSERT_EQ(it == cit, false);
}

TEST(map_mod, remove_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {5, 51}});
  s21::map<int, int>::iterator it = m1.begin();
  m1.erase(++it);
  it = m1.begin();
  ASSERT_EQ((*++it).first, 3);
}

TEST(map_mod, swap_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {5, 51}, {3, 33}});
  s21::map<int, int> m2({{999, 0}, {45, 2}});
  m1.swap(m2);
  EXPECT_EQ(m1.contains(45), true);
  EXPECT_EQ(m1.contains(1), false);
}

TEST(map_mod, clear_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {5, 51}});
  m1.clear();
  ASSERT_EQ(m1.empty(), true);
}

TEST(map_mod, clear_01) {
  s21::map<int, int> m1;
  m1.clear();
  ASSERT_EQ(m1.empty(), true);
}

TEST(map_main, copy_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {4, 0}});
  s21::map<int, int> m2 = m1;
  m2 = m2;
  ASSERT_EQ(m2.size(), 4);
}

TEST(map_main, move_00) {
  s21::map<int, int> m1({{1, 21}, {2, 42}, {3, 33}, {4, 0}});
  s21::map<int, int> m2(std::move(m1));
  ASSERT_EQ(m2.size(), 4);
  s21::map<int, int> m3({{9, 99}, {10, 100}});
  m3 = std::move(m1);
  ASSERT_EQ(m3.size(), 0);
}

TEST(map_mod, insert_01) {
  s21::map<std::string, int> m1{{"One", 1}, {"Two", 2}, {"Three", 3}};
  m1.insert("Four", 4);
  s21::map<std::string, int> m2{{"Seven", 7}, {"Six", 6}, {"Five", 5}};
  m1.merge(m2);
  auto it = m1.begin();
  EXPECT_EQ((*it).first, "Five");
  m1.insert_or_assign("abc", 123);
  m1.insert_or_assign("abc", 321);
}

TEST(map_access, at_00) {
  s21::map<std::string, int> m1{{"One", 1}, {"Two", 2}, {"Three", 3}};
  EXPECT_EQ(m1.at("One"), 1);
  EXPECT_EQ(m1["Three"], 3);
}

TEST(map_mod, insert_02) {
  s21::map<int, int> m1{{3, 1}, {2, 2}, {1, 3}};
  m1.insert_many(std::make_pair<int, int>(4, -1),
                 std::make_pair<int, int>(-1, 4));
  EXPECT_EQ(m1.contains(-1), true);
  EXPECT_EQ(m1.contains(4), true);
}

class Hui {
  public:
    void print();
};

void Hui::print() {
  
}