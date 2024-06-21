#include "../s21_lib/s21_set.h"

#include <gtest/gtest.h>

#include <set>

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

template <typename T>
struct greater_comparator {
  bool operator()(const T &a, const T &b) const { return a > b; }
};

TEST(set_test_eq, def_constructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test_eq, copy_constructor) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21::set<int> s21_set_copy(s21_set);

  std::set<int> std_set;
  std_set.insert(1);
  std_set.insert(2);
  std::set<int> std_set_copy(std_set);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());

  EXPECT_TRUE(containers_equal(s21_set_copy.begin(), s21_set_copy.end(),
                               std_set_copy.begin(), std_set_copy.end()));
}

TEST(set_test_eq, move_constructor) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21::set<int> s21_set_move(std::move(s21_set));

  std::set<int> std_set;
  std_set.insert(1);
  std_set.insert(2);
  std::set<int> std_set_move(std::move(std_set));

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_move.size(), std_set_move.size());

  EXPECT_TRUE(containers_equal(s21_set_move.begin(), s21_set_move.end(),
                               std_set_move.begin(), std_set_move.end()));
}

TEST(set_test_eq, initializer_constructor) {
  const s21::set<int> s21_set{20, 10, 30};
  const std::set<int> std_set{20, 10, 30};

  EXPECT_EQ(s21_set.size(), std_set.size());

  EXPECT_TRUE(containers_equal(s21_set.cbegin(), s21_set.cend(),
                               std_set.cbegin(), std_set.cend()));
}

TEST(set_test_eq, operator) {
  s21::set<int> s21_set({20, 10, 30});
  s21::set<int> s21_set_operator = s21_set;

  std::set<int> std_set({20, 10, 30});
  std::set<int> std_set_operator = std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_operator.size(), std_set_operator.size());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
  EXPECT_TRUE(containers_equal(s21_set_operator.begin(), s21_set_operator.end(),
                               std_set_operator.begin(),
                               std_set_operator.end()));
}

TEST(set_test_eq, insert_method) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));

  for (int i = 0; i < 10; ++i) {
    s21_set.insert(i);
    std_set.insert(i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
}

TEST(set_test_eq, erase_and_find_method) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));

  for (int i = 0; i < 10; ++i) {
    s21_set.insert(i);
    std_set.insert(i);
  }

  EXPECT_FALSE(s21_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));

  for (int i = 0; i < 5; ++i) {
    s21_set.erase(s21_set.find(i));
    std_set.erase(std_set.find(i));
  }
  s21_set.erase(s21_set.find(7));
  std_set.erase(std_set.find(7));

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
}

TEST(set_test_eq, merge_method) {
  s21::set<int> s21_set({1, 2, 3});
  s21::set<int> s21_set2({6, 5, 4});
  s21_set.merge(s21_set2);

  std::set<int> std_set({1, 2, 3});
  std::set<int> std_set2({6, 5, 4});
  std_set.merge(std_set2);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set2.empty(), std_set2.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
}

TEST(set_test_eq, swap_method) {
  s21::set<int> s21_set({1, 3, 2});
  s21::set<int> s21_set2({6, 5, 4, 4, 7});
  s21_set.swap(s21_set2);

  std::set<int> std_set({1, 2, 3});
  std::set<int> std_set2({6, 5, 4, 7});
  std_set.swap(std_set2);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set2.size(), std_set2.size());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
  EXPECT_TRUE(containers_equal(s21_set2.begin(), s21_set2.end(),
                               std_set2.begin(), std_set2.end()));
}

TEST(set_test_eq, clear_method) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  for (int i = 0; i < 10; ++i) {
    s21_set.insert(i);
    std_set.insert(i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));

  s21_set.clear();
  std_set.clear();

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
}

// TEST(set_test_eq, max_size_method)
// {
//   s21::set<int> s21_set;
//   std::set<int> std_set;

//   EXPECT_EQ(s21_set.max_size(), std_set.max_size());
// }

TEST(set_test_eq, empty_method) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test_eq, noempty_method) {
  s21::set<int> s21_set({1, 2});
  std::set<int> std_set({1, 2});

  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_test_eq, iterator_test) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());

  auto it = s21_set.begin();
  auto std_it = std_set.begin();
  while (it != s21_set.end() && std_it != std_set.end()) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(set_test_eq, greater_comparator) {
  s21::set<int, greater_comparator<int>> s21_set({2, 5, 1, 3, 8});
  std::set<int, greater_comparator<int>> std_set({2, 5, 1, 3, 8});

  EXPECT_TRUE(containers_equal(s21_set.begin(), s21_set.end(), std_set.begin(),
                               std_set.end()));
}

TEST(set_test, contains_method) {
  s21::set<int> s21_set;

  for (int i = 0; i < 10; ++i) {
    s21_set.insert(i);
  }

  EXPECT_TRUE(s21_set.contains(2));
  EXPECT_TRUE(s21_set.contains(3));
  EXPECT_TRUE(s21_set.contains(5));

  EXPECT_FALSE(s21_set.contains(20));
}

TEST(set_test, multiple_insert) {
  s21::set<int> s21_set;

  auto results = s21_set.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(s21_set.size(), 5U);

  for (const auto &result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(set_test, multiple_insert_with_duplicates) {
  s21::set<int> s21_set;

  auto results = s21_set.insert_many(1, 2, 3, 3, 4, 5);

  EXPECT_EQ(s21_set.size(), 5U);

  for (size_t i = 0; i < results.size(); ++i) {
    if (i == 3) {
      EXPECT_FALSE(results[i].second);
    } else {
      EXPECT_TRUE(results[i].second);
    }
  }
}

TEST(set_test, single_element_insert) {
  s21::set<int> s21_set;

  auto results = s21_set.insert_many(42);

  EXPECT_EQ(s21_set.size(), 1U);

  EXPECT_TRUE(results[0].second);
}