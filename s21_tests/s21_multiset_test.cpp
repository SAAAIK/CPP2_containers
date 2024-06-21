#include "../s21_lib/s21_multiset.h"

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

TEST(mutltiset_test_eq, def_constructor) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test_eq, copy_constructor) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(1);
  s21_multiset.insert(2);
  s21_multiset.insert(2);
  s21::multiset<int> s21_multiset_copy(s21_multiset);

  std::multiset<int> std_multiset;
  std_multiset.insert(1);
  std_multiset.insert(2);
  std_multiset.insert(2);
  std::multiset<int> std_multiset_copy(std_multiset);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset_copy.size(), std_multiset_copy.size());

  EXPECT_TRUE(
      containers_equal(s21_multiset_copy.begin(), s21_multiset_copy.end(),
                       std_multiset_copy.begin(), std_multiset_copy.end()));
}

TEST(multiset_test_eq, move_constructor) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(3);
  s21_multiset.insert(1);
  s21_multiset.insert(3);
  s21_multiset.insert(3);

  s21::multiset<int> s21_multiset_move(std::move(s21_multiset));

  std::multiset<int> std_multiset;
  std_multiset.insert(3);
  std_multiset.insert(1);
  std_multiset.insert(3);
  std_multiset.insert(3);

  std::multiset<int> std_multiset_move(std::move(std_multiset));

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset_move.size(), std_multiset_move.size());

  EXPECT_TRUE(
      containers_equal(s21_multiset_move.begin(), s21_multiset_move.end(),
                       std_multiset_move.begin(), std_multiset_move.end()));
}

TEST(multiset_test_eq, initializer_constructor) {
  const s21::multiset<int> s21_multiset{20, 10, 30, 20, 20};
  const std::multiset<int> std_multiset{20, 10, 30, 20, 20};

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  EXPECT_TRUE(containers_equal(s21_multiset.cbegin(), s21_multiset.cend(),
                               std_multiset.cbegin(), std_multiset.cend()));
}

TEST(multiset_test_eq, operator) {
  s21::multiset<int> s21_multiset({20, 10, 30});
  s21::multiset<int> s21_multiset_operator = s21_multiset;

  std::multiset<int> std_multiset({20, 10, 30});
  std::multiset<int> std_multiset_operator = std_multiset;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset_operator.size(), std_multiset_operator.size());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
  EXPECT_TRUE(containers_equal(
      s21_multiset_operator.begin(), s21_multiset_operator.end(),
      std_multiset_operator.begin(), std_multiset_operator.end()));
}

TEST(multiset_test_eq, insert_method) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));

  for (int i = 0; i < 10; ++i) {
    s21_multiset.insert(i);
    std_multiset.insert(i);
  }

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
}

TEST(multiset_test_eq, erase_and_find_method) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));

  for (int i = 0; i < 10; ++i) {
    s21_multiset.insert(i);
    std_multiset.insert(i);
  }

  EXPECT_FALSE(s21_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));

  for (int i = 0; i < 5; ++i) {
    s21_multiset.erase(s21_multiset.find(i));
    std_multiset.erase(std_multiset.find(i));
  }
  s21_multiset.erase(s21_multiset.find(7));
  std_multiset.erase(std_multiset.find(7));

  EXPECT_EQ(s21_multiset.size(), s21_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
}

TEST(multiset_test_eq, merge_method) {
  s21::multiset<int> s21_multiset({1, 2, 3});
  s21::multiset<int> s21_multiset2({6, 5, 4});
  s21_multiset.merge(s21_multiset2);

  std::multiset<int> std_multiset({1, 2, 3});
  std::multiset<int> std_multiset2({6, 5, 4});
  std_multiset.merge(std_multiset2);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset2.empty(), std_multiset2.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
}

TEST(multiset_test_eq, swap_method) {
  s21::multiset<int> s21_multiset({1, 3, 2});
  s21::multiset<int> s21_multiset2({6, 5, 4, 4, 7});
  s21_multiset.swap(s21_multiset2);

  std::multiset<int> std_multiset({1, 2, 3});
  std::multiset<int> std_multiset2({6, 5, 4, 4, 7});
  std_multiset.swap(std_multiset2);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset2.size(), std_multiset2.size());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
  EXPECT_TRUE(containers_equal(s21_multiset2.begin(), s21_multiset2.end(),
                               std_multiset2.begin(), std_multiset2.end()));
}

TEST(multiset_test_eq, clear_method) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  for (int i = 0; i < 10; ++i) {
    s21_multiset.insert(i);
    std_multiset.insert(i);
  }

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));

  s21_multiset.clear();
  std_multiset.clear();

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
}

// TEST(multiset_test_eq, max_size_method) {
//   s21::multiset<int> s21_multiset;
//   std::multiset<int> std_multiset;

//   EXPECT_EQ(s21_multiset.max_size(), std_multiset.max_size());
// }

TEST(multiset_test_eq, empty_method) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test_eq, noempty_method) {
  s21::multiset<int> s21_multiset({1, 2});
  std::multiset<int> std_multiset({1, 2});

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test_eq, iterator_test) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  auto it = s21_multiset.begin();
  auto std_it = std_multiset.begin();
  while (it != s21_multiset.end() && std_it != std_multiset.end()) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(multiset_test_eq, greater_comparator) {
  s21::multiset<int, greater_comparator<int>> s21_multiset({2, 5, 1, 3, 8});
  std::multiset<int, greater_comparator<int>> std_multiset({2, 5, 1, 3, 8});

  EXPECT_TRUE(containers_equal(s21_multiset.begin(), s21_multiset.end(),
                               std_multiset.begin(), std_multiset.end()));
}

TEST(multiset_test_eq, upper_lower_bound_test) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 4, 5};

  auto lower_s21 = s21_multiset.lower_bound(3);
  auto lower_std = std_multiset.lower_bound(3);

  auto upper_s21 = s21_multiset.upper_bound(3);
  auto upper_std = std_multiset.upper_bound(3);

  ASSERT_EQ(*lower_s21, *lower_std);
  ASSERT_EQ(*upper_s21, *upper_std);
}

TEST(multiset_test_eq, equal_range_test) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 4, 5};

  auto s21_range = s21_multiset.equal_range(4);
  auto std_range = std_multiset.equal_range(4);

  auto s21_it = s21_range.first;
  auto std_it = std_range.first;
  for (; s21_it != s21_range.second && std_it != std_range.second;
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }

  EXPECT_TRUE(s21_it == s21_range.second && std_it == std_range.second);
}

TEST(multiset_test, contains_method) {
  s21::multiset<int> s21_multiset;

  for (int i = 0; i < 10; ++i) {
    s21_multiset.insert(i);
  }

  EXPECT_TRUE(s21_multiset.contains(2));
  EXPECT_TRUE(s21_multiset.contains(3));
  EXPECT_TRUE(s21_multiset.contains(5));

  EXPECT_FALSE(s21_multiset.contains(20));
}