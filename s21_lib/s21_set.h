#ifndef S21_SET
#define S21_SET

#include <vector>

#include "red_black_tree/rb_tree.h"

namespace s21 {
template <typename data_type, typename compare = std::less<data_type>>
class set : public rb_tree<data_type, compare> {
  using base = rb_tree<data_type, compare>;

 public:
  using iterator = typename base::iterator;
  using const_iterator = typename base::const_iterator;

  set() : base() {}
  set(std::initializer_list<data_type> const &items);
  set(const set &other) : base(other) {}
  set(set &&other) noexcept : base(std::move(other)) {}
  ~set() = default;
  set &operator=(set &&other) noexcept;

  iterator begin() { return base::begin(); }
  iterator end() { return base::end(); }
  iterator find(const data_type &value) { return base::find(value); }

  const_iterator cbegin() const { return base::cbegin(); }
  const_iterator cend() const { return base::cend(); }
  const_iterator find(const data_type &value) const {
    return base::find(value);
  }

  bool empty() const noexcept { return base::empty(); }
  size_t size() const noexcept { return base::size(); }
  size_t max_size() const noexcept { return base::max_size(); }

  void clear() { base::clear(); }
  std::pair<iterator, bool> insert(const data_type &value) {
    return this->insert_data(value);
  }
  void erase(iterator pos) { base::erase(pos); }
  void swap(set &other) noexcept { base::swap(other); }
  void merge(set &other) { base::merge(other); }
  bool contains(const data_type &key) const {
    return this->find(key) != this->cend();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace s21

template <typename data_type, typename compare>
s21::set<data_type, compare>::set(
    std::initializer_list<data_type> const &items) {
  for (auto &item : items) {
    this->insert_data(item);
  }
}

template <typename data_type, typename compare>
s21::set<data_type, compare> &s21::set<data_type, compare>::operator=(
    set &&other) noexcept {
  if (this != &other) {
    base::operator=(std::move(other));
  }
  return *this;
}

template <typename data_type, typename compare>
template <typename... Args>
std::vector<std::pair<typename s21::set<data_type, compare>::iterator, bool>>
s21::set<data_type, compare>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert_data(std::forward<Args>(args))), ...);
  return results;
}

#endif