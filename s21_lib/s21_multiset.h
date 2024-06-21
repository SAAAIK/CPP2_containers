#ifndef S21_MULTISET
#define S21_MULTISET

#include "red_black_tree/rb_tree.h"

namespace s21 {

template <typename data_type, typename compare = std::less<data_type>>
class multiset : public rb_tree<data_type, compare> {
  using base = rb_tree<data_type, compare>;

 public:
  using iterator = typename base::iterator;
  using const_iterator = typename base::const_iterator;

  multiset() : base() {}
  multiset(std::initializer_list<data_type> const& items);
  multiset(const multiset& other) : base(other) {}
  multiset(multiset&& other) noexcept : base(std::move(other)) {}
  ~multiset() = default;  // +

  multiset& operator=(multiset&& other) noexcept;

  iterator begin() { return base::begin(); }
  iterator end() { return base::end(); }
  iterator find(const data_type& value) { return base::find(value); }

  const_iterator cbegin() const { return base::cbegin(); }
  const_iterator cend() const { return base::cend(); }
  const_iterator find(const data_type& value) const {
    return base::find(value);
  }

  bool empty() const noexcept { return base::empty(); }
  size_t size() const noexcept { return base::size(); }
  size_t max_size() const noexcept { return base::max_size(); }

  void clear() { base::clear(); }
  iterator insert(const data_type& value) { return insert_data(value).first; }
  void erase(iterator pos);
  void swap(multiset& other) noexcept { base::swap(other); }
  void merge(multiset& other) { base::merge(other); }
  bool contains(const data_type& key) const {
    return this->find(key) != this->cend();
  }

  iterator upper_bound(const data_type& key);
  iterator lower_bound(const data_type& key);

  std::pair<iterator, iterator> equal_range(const data_type& value);

 private:
  std::pair<typename rb_tree<data_type, compare>::iterator, bool> insert_data(
      const data_type& data) override;
};
}  // namespace s21

template <typename data_type, typename compare>
s21::multiset<data_type, compare>::multiset(
    std::initializer_list<data_type> const& items) {
  for (auto& item : items) {
    this->insert_data(item);
  }
}

template <typename data_type, typename compare>
s21::multiset<data_type, compare>& s21::multiset<data_type, compare>::operator=(
    multiset&& other) noexcept {
  if (this != &other) {
    base::operator=(std::move(other));
  }
  return *this;
}

template <typename data_type, typename compare>
void s21::multiset<data_type, compare>::erase(iterator pos) {
  const data_type& key = *pos;
  auto range = equal_range(key);
  for (auto it = range.first; it != range.second;) {
    auto current = it++;
    if (current == pos) {
      base::erase(current);
    }
  }
}

template <typename data_type, typename compare>
typename s21::multiset<data_type, compare>::iterator
s21::multiset<data_type, compare>::upper_bound(const data_type& key) {
  typename base::node* current_node = base::root_;
  iterator upper_bound = base::end();
  while (current_node != nullptr) {
    if (base::compare_(key, current_node->data_)) {
      upper_bound = iterator(current_node, this);
      current_node = current_node->left_;
    } else {
      current_node = current_node->right_;
    }
  }
  return upper_bound;
}

template <typename data_type, typename compare>
typename s21::multiset<data_type, compare>::iterator
s21::multiset<data_type, compare>::lower_bound(const data_type& key) {
  typename base::node* current_node = base::root_;
  iterator lower_bound = base::end();
  while (current_node != nullptr) {
    if (!base::compare_(current_node->data_, key)) {
      lower_bound = iterator(current_node, this);
      current_node = current_node->left_;
    } else {
      current_node = current_node->right_;
    }
  }
  return lower_bound;
}

template <typename data_type, typename compare>
std::pair<typename s21::multiset<data_type, compare>::iterator,
          typename s21::multiset<data_type, compare>::iterator>
s21::multiset<data_type, compare>::equal_range(const data_type& value) {
  iterator first = lower_bound(value);
  iterator last = upper_bound(value);
  return std::make_pair(first, last);
}

template <typename data_type, typename compare>
std::pair<typename s21::multiset<data_type, compare>::iterator, bool>
s21::multiset<data_type, compare>::insert_data(const data_type& data) {
  typename base::node* current_node = base::root_;
  typename base::node* parent_node = nullptr;
  while (current_node != nullptr) {
    parent_node = current_node;
    if (this->compare_(data, current_node->data_)) {
      current_node = current_node->left_;
    } else {
      current_node = current_node->right_;
    }
  }
  typename base::node* new_node = new typename base::node(data, nullptr);
  new_node->parent_ = parent_node;

  if (parent_node == nullptr) {
    base::root_ = new_node;
  } else if (!this->compare_(data, parent_node->data_)) {
    parent_node->right_ = new_node;
  } else {
    parent_node->left_ = new_node;
  }
  this->fix_violation(new_node);
  ++base::size_;
  return std::make_pair(typename base::iterator(new_node, this), true);
}

#endif