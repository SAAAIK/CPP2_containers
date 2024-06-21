#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "../s21_lib/s21_list.h"

template <typename iterator1, typename iterator2>
bool containers_equal(iterator1 begin1, iterator1 end1, iterator2 begin2,
                      iterator2 end2) {
  for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2) {
    if (*begin1 != *begin2) {
      return false;
    }
  }
  return begin1 == end1 && begin2 == end2;
}

TEST(List, Constructor_Default) {
  s21::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Constructor_Size) {
  s21::list<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
}

TEST(List, Constructor_List) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));

  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Constructor_Copy) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21::list<int> our_copy(our_list);
  std::list<int> std_copy(std_list);

  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());

  EXPECT_TRUE(containers_equal(our_copy.begin(), our_copy.end(),
                               std_copy.begin(), std_copy.end()));
}

TEST(List, Operator_Copy) {
  s21::list<int> our_list = {1, 2, 5};
  std::list<int> std_list = {1, 2, 5};

  s21::list<int> our_copy = our_list;
  std::list<int> std_copy = std_list;

  EXPECT_TRUE(containers_equal(our_copy.begin(), our_copy.end(),
                               std_copy.begin(), std_copy.end()));
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21::list<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));

  EXPECT_EQ(our_list.size(), std_list.size());
  EXPECT_EQ(our_copy.size(), std_copy.size());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
  EXPECT_TRUE(containers_equal(our_copy.begin(), our_copy.end(),
                               std_copy.begin(), std_copy.end()));
}

TEST(List, Operator_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21::list<int> our_copy = std::move(our_list);
  std::list<int> std_copy = std::move(std_list);

  EXPECT_EQ(our_list.size(), std_list.size());
  EXPECT_EQ(our_copy.size(), std_copy.size());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
  EXPECT_TRUE(containers_equal(our_copy.begin(), our_copy.end(),
                               std_copy.begin(), std_copy.end()));
}

TEST(List, Push_Front) {
  s21::list<int> our_list;
  std::list<int> std_list;

  our_list.push_front(1);
  std_list.push_front(1);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_front(2);
  std_list.push_front(2);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_front(3);
  std_list.push_front(3);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
}

TEST(List, Push_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;

  our_list.push_back(1);
  std_list.push_back(1);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(2);
  std_list.push_back(2);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(3);
  std_list.push_back(3);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
}

TEST(List, Pop_Front) {
  s21::list<int> our_list;
  std::list<int> std_list;

  our_list.push_back(1);
  std_list.push_back(1);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(2);
  std_list.push_back(2);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(3);
  std_list.push_back(3);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.pop_front();
  std_list.pop_front();

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
}

TEST(List, Pop_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;

  our_list.push_back(1);
  std_list.push_back(1);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(2);
  std_list.push_back(2);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.push_back(3);
  std_list.push_back(3);

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  our_list.pop_back();
  std_list.pop_back();

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());

  EXPECT_TRUE(containers_equal(our_list.begin(), our_list.end(),
                               std_list.begin(), std_list.end()));
}

TEST(List, Iterator_Begin) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto our_it = our_list.begin();
  ;
  auto std_it = std_list.begin();
  ;

  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_BeginPlusAndMinus) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto our_it = our_list.begin();
  ++our_it;

  auto std_it = std_list.begin();
  ++std_it;

  EXPECT_EQ(*our_it, *std_it);

  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, max_size_method) {
  s21::list<std::string> our_list;
  std::list<std::string> std_list;

  EXPECT_EQ(our_list.max_size(), std_list.max_size());
}

TEST(List, Iterator_End_Last) {
  s21::list<int> our_list = {1, 2, 3};

  if (!our_list.empty()) {
    auto our_it = our_list.end();
    --our_it;
  }
}

TEST(List, Insert) {
  s21::list<int> our_list;
  std::list<int> std_list;
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Splice) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(List, Merge) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(List, Reverse) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Unique) {
  s21::list<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Sort) {
  s21::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Insert_Many) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, Insert_Many_Front) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, insert_many_back_empty_list) {
  s21::list<int> my_list;
  my_list.insert_many_back(1, 2, 3, 4, 5);

  ASSERT_EQ(my_list.size(), 5U);
  EXPECT_EQ(my_list.front(), 1);
  EXPECT_EQ(my_list.back(), 5);

  int expected_value = 1;
  for (auto it = my_list.begin(); it != my_list.end(); ++it, ++expected_value) {
    EXPECT_EQ(*it, expected_value);
  }
}

TEST(List, insert_many_back_nonempty_list) {
  s21::list<int> my_list;
  my_list.push_back(10);
  my_list.push_back(20);

  my_list.insert_many_back(1, 2, 3);

  ASSERT_EQ(my_list.size(), 5U);
  EXPECT_EQ(my_list.front(), 10);
  EXPECT_EQ(my_list.back(), 3);

  std::vector<int> expected_values = {10, 20, 1, 2, 3};
  auto it = my_list.begin();
  for (size_t i = 0; i < expected_values.size(); ++i, ++it) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}

TEST(List, insert_many_back_different_types) {
  s21::list<std::string> my_list;
  my_list.insert_many_back("hello", "world", "test");

  ASSERT_EQ(my_list.size(), 3U);
  EXPECT_EQ(my_list.front(), "hello");
  EXPECT_EQ(my_list.back(), "test");

  std::vector<std::string> expected_values = {"hello", "world", "test"};
  auto it = my_list.begin();
  for (size_t i = 0; i < expected_values.size(); ++i, ++it) {
    EXPECT_EQ(*it, expected_values[i]);
  }
}
