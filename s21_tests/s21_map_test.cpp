#include "../s21_lib/s21_map.h"

#include <gtest/gtest.h>

template <typename iterator1, typename iterator2>
bool containers_equal(iterator1 begin1, iterator1 end1, iterator2 begin2,
                      iterator2 end2) {
  for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2) {
    if (std::tie(begin1->first, begin1->second) !=
        std::tie(begin2->first, begin2->second)) {
      return false;
    }
  }
  return begin1 == end1 && begin2 == end2;
}

TEST(map_test_eq, def_constructor) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map_test_eq, copy_constructor) {
  s21::map<int, std::string> s21_map;
  s21_map.insert({1, "one"});
  s21_map.insert({2, "two"});
  s21::map<int, std::string> s21_map_copy(s21_map);

  std::map<int, std::string> std_map;
  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std::map<int, std::string> std_map_copy(std_map);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());

  EXPECT_TRUE(containers_equal(s21_map_copy.begin(), s21_map_copy.end(),
                               std_map_copy.begin(), std_map_copy.end()));
}

TEST(map_test_eq, initializer_constructor) {
  s21::map<int, std::string> s21_map{{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> std_map{{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.size(), std_map.size());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
}

TEST(map_test_eq, move_constructor) {
  s21::map<int, std::string> s21_map;
  s21_map.insert({1, "one"});
  s21_map.insert({2, "two"});
  s21::map<int, std::string> s21_map_move(std::move(s21_map));

  std::map<int, std::string> std_map;
  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std::map<int, std::string> std_map_move(std::move(std_map));

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());

  EXPECT_TRUE(containers_equal(s21_map_move.begin(), s21_map_move.end(),
                               std_map_move.begin(), std_map_move.end()));
}

TEST(map_test_eq, operator_assignment) {
  s21::map<int, std::string> s21_map(
      {{20, "twenty"}, {10, "ten"}, {30, "thirty"}});
  s21::map<int, std::string> s21_map_operator = s21_map;

  std::map<int, std::string> std_map(
      {{20, "twenty"}, {10, "ten"}, {30, "thirty"}});
  std::map<int, std::string> std_map_operator = std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_operator.size(), std_map_operator.size());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
  EXPECT_TRUE(containers_equal(s21_map_operator.begin(), s21_map_operator.end(),
                               std_map_operator.begin(),
                               std_map_operator.end()));
}

TEST(map_test_eq, at_method) {
  s21::map<int, std::string> s21_map({{1, "one"}, {2, "two"}, {3, "three"}});
  std::map<int, std::string> std_map({{1, "one"}, {2, "two"}, {3, "three"}});

  EXPECT_EQ(s21_map.at(1), std_map.at(1));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
  EXPECT_EQ(s21_map.at(3), std_map.at(3));
}

// TEST(map_test_eq, at_method_nonexistent_key)
// {
//   s21::map<int, std::string> s21_map({{1, "one"}, {2, "two"}, {3, "three"}});
//   std::map<int, std::string> std_map({{1, "one"}, {2, "two"}, {3, "three"}});

//   try
//   {
//     s21_map.at(4);
//     FAIL() << "Expected std::out_of_range exception";
//   }
//   catch (const std::out_of_range &e)
//   {
//     EXPECT_EQ(e.what(), std::string("map::at"));
//   }
//   catch (...)
//   {
//     FAIL() << "Expected std::out_of_range exception";
//   }

//   try
//   {
//     std_map.at(4);
//     FAIL() << "Expected std::out_of_range exception";
//   }
//   catch (const std::out_of_range &e)
//   {
//     EXPECT_EQ(e.what(), std::string("map::at"));
//   }
//   catch (...)
//   {
//     FAIL() << "Expected std::out_of_range exception";
//   }
// }

TEST(map_test_eq, operator_brackets) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  s21_map[1] = "one";
  s21_map[2] = "two";
  s21_map[3] = "three";
  std_map[1] = "one";
  std_map[2] = "two";
  std_map[3] = "three";

  EXPECT_EQ(s21_map.size(), std_map.size());
  for (const auto &[key, value] : s21_map) {
    EXPECT_EQ(s21_map[key], std_map[key]);
  }

  s21_map[4] = "four";
  std_map[4] = "four";

  EXPECT_EQ(s21_map.size(), std_map.size());
  for (const auto &[key, value] : s21_map) {
    EXPECT_EQ(s21_map[key], std_map[key]);
  }
}

TEST(map_test_eq, iterator_test) {
  s21::map<int, std::string> s21_map = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  std::map<int, std::string> std_map = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  EXPECT_EQ(s21_map.size(), std_map.size());

  auto it = s21_map.begin();
  auto std_it = std_map.begin();
  while (it != s21_map.end() && std_it != std_map.end()) {
    EXPECT_EQ(it->first, std_it->first);
    EXPECT_EQ(it->second, std_it->second);
    ++it;
    ++std_it;
  }
}

TEST(map_test_eq, iter_begin) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto my_it = s21_map.begin();
  auto std_it = std_map.begin();
  while (my_it != s21_map.end() && std_it != std_map.end()) {
    EXPECT_EQ(my_it->first, std_it->first);
    EXPECT_EQ(my_it->second, std_it->second);
    ++my_it;
    ++std_it;
  }
}

TEST(map_test_eq, empty_method) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;

  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map_test_eq, noempty_method) {
  s21::map<int, int> s21_map{{1, 2}, {2, 3}};
  std::map<int, int> std_map{{1, 2}, {2, 3}};

  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map_test_eq, max_size_method) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.max_size(), std_map.max_size());
}

TEST(map_test_eq, clear_method) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;

  for (int i = 0; i < 10; ++i) {
    s21_map[i] = i;
    std_map[i] = i;
  }

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));

  s21_map.clear();
  std_map.clear();

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
}

TEST(map_test, insert_method) {
  s21::map<int, std::string> map;

  auto result = map.insert(42, "value");

  EXPECT_TRUE(result.second);

  EXPECT_EQ(result.first->first, 42);
  EXPECT_EQ(result.first->second, "value");

  result = map.insert(42, "new_value");

  EXPECT_FALSE(result.second);

  EXPECT_EQ(result.first->first, 42);
  EXPECT_EQ(result.first->second, "value");
  EXPECT_EQ(map.size(), 1U);
}

TEST(map_test, insert_or_assign_method) {
  s21::map<int, std::string> map;
  map.insert(42, "value");

  auto result = map.insert_or_assign(std::make_pair(42, "new_value"));

  EXPECT_FALSE(result.second);

  EXPECT_EQ(result.first->first, 42);
  EXPECT_EQ(result.first->second, "new_value");

  result = map.insert_or_assign(std::make_pair(43, "value_43"));

  EXPECT_TRUE(result.second);

  EXPECT_EQ(result.first->first, 43);
  EXPECT_EQ(result.first->second, "value_43");
}

TEST(map_test_eq, erase_and_find_method) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));

  for (int i = 0; i < 10; ++i) {
    s21_map.insert(std::make_pair(i, "value_" + std::to_string(i)));
    std_map.insert(std::make_pair(i, "value_" + std::to_string(i)));
  }

  EXPECT_FALSE(s21_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));

  for (int i = 0; i < 5; ++i) {
    s21_map.erase(s21_map.find(i));
    std_map.erase(std_map.find(i));
  }

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
}

TEST(map_test_eq, merge_method) {
  s21::map<int, std::string> s21_map({{1, "one"}, {2, "two"}, {3, "three"}});
  s21::map<int, std::string> s21_map2({{6, "six"}, {5, "five"}, {4, "four"}});
  s21_map.merge(s21_map2);

  std::map<int, std::string> std_map({{1, "one"}, {2, "two"}, {3, "three"}});
  std::map<int, std::string> std_map2({{6, "six"}, {5, "five"}, {4, "four"}});
  std_map.merge(std_map2);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map2.empty(), std_map2.empty());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
}

TEST(map_test_eq, swap_method) {
  s21::map<int, std::string> s21_map({{1, "one"}, {3, "three"}, {2, "two"}});
  s21::map<int, std::string> s21_map2(
      {{6, "six"}, {5, "five"}, {4, "four"}, {4, "four2"}, {7, "seven"}});
  s21_map.swap(s21_map2);

  std::map<int, std::string> std_map({{1, "one"}, {2, "two"}, {3, "three"}});
  std::map<int, std::string> std_map2(
      {{6, "six"}, {5, "five"}, {4, "four"}, {7, "seven"}});
  std_map.swap(std_map2);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map2.size(), std_map2.size());

  EXPECT_TRUE(containers_equal(s21_map.begin(), s21_map.end(), std_map.begin(),
                               std_map.end()));
  EXPECT_TRUE(containers_equal(s21_map2.begin(), s21_map2.end(),
                               std_map2.begin(), std_map2.end()));
}

TEST(map_test, contains_method) {
  s21::map<int, std::string> s21_map;

  s21_map.insert({1, "one"});
  s21_map.insert({2, "two"});
  s21_map.insert({3, "three"});

  EXPECT_TRUE(s21_map.contains(2));
  EXPECT_TRUE(s21_map.contains(3));

  EXPECT_FALSE(s21_map.contains(5));
}

TEST(map_insert_many_test, basic_insertion) {
  s21::map<int, std::string> my_map;

  auto results =
      my_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                         std::make_pair(3, "three"));

  ASSERT_EQ(results.size(), 3U);

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_TRUE(my_map.contains(1));
  EXPECT_TRUE(my_map.contains(2));
  EXPECT_TRUE(my_map.contains(3));
}