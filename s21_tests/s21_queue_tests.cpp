#include <gtest/gtest.h>

#include <queue>

#include "../s21_lib/s21_queue.h"

template <typename value_type>
bool check_eq(s21::queue<value_type> m_queue,
              std::queue<value_type> orig_queue) {
  bool result = true;
  if (m_queue.size() == orig_queue.size()) {
    while (!m_queue.empty() && !orig_queue.empty()) {
      if (m_queue.front() != orig_queue.front()) {
        result = false;
        break;
      }
      m_queue.pop();
      orig_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue_test, construct_def_empty) {
  s21::queue<int> my;
  EXPECT_THROW(my.back(), std::logic_error);

  s21::queue<int> my1;
  my1.push(1);
  my1.push(2);
  my1.push(3);
  my1.push(4);

  std::queue<int> orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  orig.push(4);

  int my_front = my1.front();
  int orig_front = orig.front();
  int my_back = my1.back();
  int orig_back = orig.back();
  EXPECT_EQ((int)my1.size(), 4);
  EXPECT_EQ(my_front, orig_front);
  EXPECT_EQ(my_back, orig_back);
}

TEST(Queue_test, front) {
  s21::queue<int> my;
  EXPECT_THROW(my.front(), std::logic_error);
}

TEST(Queue_test, empty) {
  s21::queue<int> my1;
  std::queue<int> orig;
  EXPECT_EQ(my1.empty(), orig.empty());
}

TEST(Queue_test, swap) {
  s21::queue<int> qu = {1, 2, 3, 5, 6, 7};
  s21::queue<int> qu2 = {55, 22, 53, 8342, 5643, 422};
  qu.swap(qu2);
  EXPECT_EQ(qu.back(), 422);
  EXPECT_EQ(qu.front(), 55);
}

TEST(Queue_test, not_eq_length) {
  s21::queue<int> qu = {1, 2, 3, 5, 6, 7};
  s21::queue<int> qu2 = {55, 22, 53, 8342, 5643, 422, 44, 76, 33};
  qu.swap(qu2);
  EXPECT_EQ(qu.back(), 33);
  EXPECT_EQ(qu.front(), 55);
}

TEST(Queue_test, empty_swap) {
  s21::queue<int> qu;
  s21::queue<int> qu2;
  qu.swap(qu2);
  EXPECT_THROW(qu.back(), std::logic_error);
  EXPECT_THROW(qu.front(), std::logic_error);
}

TEST(Queue_test, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(check_eq(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(check_eq(my_queue, std_queue));
}

TEST(Queue_test, pop) {
  s21::queue<int> my{1, 3, 10, -5, 20, 21};
  std::queue<int> orig;
  orig.push(1);
  orig.push(3);
  orig.push(10);
  orig.push(-5);
  orig.push(20);
  orig.push(21);
  my.pop();
  my.pop();
  orig.pop();
  orig.pop();
  EXPECT_TRUE(check_eq(my, orig));
  EXPECT_EQ(my.front(), 10);

  s21::queue<int> empty_qu;
  EXPECT_THROW(empty_qu.back(), std::logic_error);
  EXPECT_THROW(empty_qu.pop(), std::logic_error);
  EXPECT_THROW(empty_qu.front(), std::logic_error);
}

TEST(Queue_test, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> my{b};
  std::queue<int> orig{b};
  EXPECT_TRUE(check_eq(my, orig));
}

TEST(Queue_test, MoveConstructor) {
  std::queue<int> orig;
  orig.push(1);
  orig.push(3);
  orig.push(10);
  orig.push(-5);
  orig.push(20);
  orig.push(21);

  s21::queue<int> my;
  my.push(1);
  my.push(3);
  my.push(10);
  my.push(-5);
  my.push(20);
  my.push(21);
  EXPECT_TRUE(check_eq(my, orig));
}