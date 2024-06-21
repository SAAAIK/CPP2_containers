#ifndef S21_MAP
#define S21_MAP

#include <vector>

#include "red_black_tree/rb_tree.h"

namespace s21 {
template <typename Key, typename T>
struct pair_compare {
  bool operator()(const std::pair<Key, T>& lhs,
                  const std::pair<Key, T>& rhs) const {
    return lhs.first < rhs.first;
  }
};

template <typename Key, typename T, typename compare = pair_compare<Key, T>>
class map : public rb_tree<std::pair<Key, T>, compare> {
  using base = rb_tree<std::pair<Key, T>, compare>;

 public:
  using iterator = typename base::iterator;
  using const_iterator = typename base::const_iterator;

  map() : base() {}
  map(std::initializer_list<std::pair<Key, T>> const& items);
  map(const map& other) : base(other) {}
  map(map&& other) noexcept : base(std::move(other)) {}
  ~map() = default;

  map& operator=(map&& other) noexcept;

  T& at(const Key& key);
  const T& at(const Key& key) const;
  T& operator[](const Key& key);

  iterator begin() { return base::begin(); }
  iterator end() { return base::end(); }
  iterator find(const Key& key) { return base::find(std::make_pair(key, T{})); }

  const_iterator cbegin() const { return base::cbegin(); }
  const_iterator cend() const { return base::cend(); }
  const_iterator find(const Key& key) const {
    return base::find(std::make_pair(key, T{}));
  }

  bool empty() const noexcept { return base::empty(); }
  size_t size() const noexcept { return base::size(); }
  size_t max_size() const noexcept { return base::max_size(); }

  void clear() { base::clear(); }
  std::pair<iterator, bool> insert(const std::pair<Key, T>& value) {
    return this->insert_data(value);
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const std::pair<Key, T>& value);
  void erase(iterator pos) { base::erase(pos); }
  void swap(map& other) noexcept { base::swap(other); }
  void merge(map& other) { base::merge(other); }
  bool contains(const Key& key) const {
    return this->find(key) != this->cend();
  }
  template <typename... Args>
  std::vector<std::pair<typename map<Key, T, compare>::iterator, bool>>
  insert_many(Args&&... args);
};
}  // namespace s21

template <typename Key, typename T, typename compare>
s21::map<Key, T, compare>::map(
    std::initializer_list<std::pair<Key, T>> const& items)
    : base() {
  for (const auto& item : items) {
    this->insert(item);
  }
}

template <typename Key, typename T, typename compare>
s21::map<Key, T, compare>& s21::map<Key, T, compare>::operator=(
    map&& other) noexcept {
  if (this != &other) {
    base::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T, typename compare>
T& s21::map<Key, T, compare>::at(const Key& key) {
  auto it = this->find(key);
  if (it == this->end()) {
    throw std::out_of_range("map::at");
  }
  return it->second;
}

template <typename Key, typename T, typename compare>
const T& s21::map<Key, T, compare>::at(const Key& key) const {
  auto it = this->find(key);
  if (it == this->cend()) {
    throw std::out_of_range("map::at");
  }
  return it->second;
}

template <typename Key, typename T, typename compare>
T& s21::map<Key, T, compare>::operator[](const Key& key) {
  auto result = this->insert(std::make_pair(key, T{}));
  return result.first->second;
}

template <typename Key, typename T, typename compare>
std::pair<typename s21::map<Key, T, compare>::iterator, bool>
s21::map<Key, T, compare>::insert(const Key& key, const T& obj) {
  std::pair<Key, T> value(key, obj);
  return this->insert(value);
}

template <typename Key, typename T, typename compare>
std::pair<typename s21::map<Key, T, compare>::iterator, bool>
s21::map<Key, T, compare>::insert_or_assign(const std::pair<Key, T>& value) {
  auto it = this->find(value.first);
  if (it != this->end()) {
    it->second = value.second;
    return {it, false};
  } else {
    return this->insert(value);
  }
}

template <typename Key, typename T, typename compare>
template <typename... Args>
std::vector<std::pair<typename s21::map<Key, T, compare>::iterator, bool>>
s21::map<Key, T, compare>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}
#endif
