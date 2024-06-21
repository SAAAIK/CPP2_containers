#ifndef S21_RB_TREE
#define S21_RB_TREE
#include <iostream>
#include <limits>
#include <stack>

namespace s21 {

template <typename data_type, typename compare = std::less<data_type>>
class rb_tree {
 protected:
  enum color_node { red, black };
  struct node;

 public:
  class iterator;
  class const_iterator;

  rb_tree() : root_(nullptr), size_(0){};
  rb_tree(const rb_tree& other);
  rb_tree(rb_tree&& other) noexcept;
  rb_tree(std::initializer_list<data_type> const& elem);
  ~rb_tree() { clear(); }

  rb_tree& operator=(rb_tree&& other) noexcept;

  iterator begin() { return iterator(root_ ? min_node(root_) : nullptr, this); }
  iterator end() { return iterator(nullptr, this); }
  iterator find(const data_type& value);

  const_iterator cbegin() const {
    return const_iterator(root_ ? min_node(root_) : nullptr, this);
  }
  const_iterator cend() const { return const_iterator(nullptr, this); }
  const_iterator find(const data_type& value) const;

  size_t size() const noexcept { return size_; }
  size_t max_size() const noexcept {
    return std::allocator_traits<std::allocator<node>>::max_size(
        std::allocator<node>());
  }
  bool empty() const noexcept { return size_ == 0; }

  void clear();
  virtual std::pair<iterator, bool> insert_data(const data_type& data);
  void erase(iterator pos);
  void swap(rb_tree& other) noexcept;
  void merge(rb_tree& other);

  // вспомогательные функции
  void print() const;
  bool is_balanced() const {
    return is_balanced_black_height(root_) && is_balanced_red_black(root_);
  }
  bool is_balanced_black_height(node* node_curr) const;
  int black_height(node* node_curr) const;
  bool is_balanced_red_black(node* node_curr) const;

 protected:
  struct node {
    data_type data_;
    node* left_;
    node* right_;
    node* parent_;
    color_node color_;
    node(const data_type& data, node* parent)
        : data_(data),
          left_(nullptr),
          right_(nullptr),
          parent_(parent),
          color_(red) {}
  };

  node* root_;
  size_t size_;
  compare compare_;

  node* copy_tree(node* src);
  node* max_node(node* node_curr) const;
  node* min_node(node* node_curr) const;
  void rotate_left(node* node_curr);
  void rotate_right(node* node_curr);
  void fix_violation(node* node_curr);
  void delete_fix(node* node_curr);
};

template <typename data_type, typename compare>
class rb_tree<data_type, compare>::iterator {
 public:
  iterator() : ptr_(nullptr), tree_(nullptr) {}
  iterator(node* ptr, rb_tree* tree) : ptr_(ptr), tree_(tree) {}
  iterator(const iterator& other) : ptr_(other.ptr_), tree_(other.tree_) {}

  data_type& operator*();
  const data_type& operator*() const;

  data_type* operator->() { return &(ptr_->data_); }
  iterator& operator=(const iterator& other);
  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  bool operator==(const iterator& other) {
    return ptr_ == other.ptr_ && tree_ == other.tree_;
  }
  bool operator!=(const iterator& other) {
    return ptr_ != other.ptr_ || tree_ != other.tree_;
  }

  node* get_node() const { return ptr_; }

 protected:
  node* ptr_;
  rb_tree* tree_;
};

template <typename data_type, typename compare>
class rb_tree<data_type, compare>::const_iterator {
 public:
  const_iterator() : ptr_(nullptr), tree_(nullptr) {}
  const_iterator(const node* ptr, const rb_tree* tree)
      : ptr_(ptr), tree_(tree) {}
  const_iterator(const const_iterator& other)
      : ptr_(other.ptr_), tree_(other.tree_) {}

  const data_type& operator*() const;
  const data_type* operator->() const { return &(ptr_->data_); }
  const_iterator& operator=(const const_iterator& other);
  const_iterator& operator++();
  const_iterator operator++(int);
  const_iterator& operator--();
  const_iterator operator--(int);
  bool operator==(const const_iterator& other) const {
    return ptr_ == other.ptr_ && tree_ == other.tree_;
  }
  bool operator!=(const const_iterator& other) const {
    return ptr_ != other.ptr_ || tree_ != other.tree_;
  }

 protected:
  const node* ptr_;
  const rb_tree* tree_;
};
}  // namespace s21

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::print() const {
  if (!root_) {
    std::cout << "Tree is empty" << std::endl;
    return;
  }
  std::stack<node*> s;
  node* current = root_;

  while (current != nullptr || !s.empty()) {
    while (current != nullptr) {
      s.push(current);
      current = current->left_;
    }

    current = s.top();
    s.pop();

    std::cout << current->data_ << " ";

    current = current->right_;
  }
  std::cout << std::endl;
}

template <typename data_type, typename compare>
bool s21::rb_tree<data_type, compare>::is_balanced_black_height(
    node* node_curr) const {
  if (node_curr == nullptr) return true;

  bool left_balanced = is_balanced_black_height(node_curr->left_);
  bool right_balanced = is_balanced_black_height(node_curr->right_);

  int left_black_height = black_height(node_curr->left_);
  int right_black_height = black_height(node_curr->right_);
  return left_balanced && right_balanced &&
         (left_black_height == right_black_height);
}

template <typename data_type, typename compare>
int s21::rb_tree<data_type, compare>::black_height(node* node_curr) const {
  if (node_curr == nullptr) return 0;
  int left_black_height = black_height(node_curr->left_);
  int right_black_height = black_height(node_curr->right_);
  int current_height = (node_curr->color_ == black) ? 1 : 0;
  return std::max(left_black_height, right_black_height) + current_height;
}

template <typename data_type, typename compare>
bool s21::rb_tree<data_type, compare>::is_balanced_red_black(
    node* node_curr) const {
  if (node_curr == nullptr) return true;
  bool left_balanced = is_balanced_red_black(node_curr->left_);
  bool right_balanced = is_balanced_red_black(node_curr->right_);
  if (node_curr->color_ == red) {
    if (node_curr->left_ && node_curr->left_->color_ != black) return false;
    if (node_curr->right_ && node_curr->right_->color_ != black) return false;
  }
  return left_balanced && right_balanced;
}

template <typename K, typename V>
s21::rb_tree<K, V>::rb_tree(const rb_tree& other) {
  if (other.root_) {
    root_ = copy_tree(other.root_);
    size_ = other.size_;
    compare_ = other.compare_;
  }
}

template <typename K, typename V>
s21::rb_tree<K, V>::rb_tree(rb_tree&& other) noexcept {
  root_ = other.root_;
  size_ = other.size_;
  compare_ = std::move(other.compare_);
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename data_type, typename compare>
s21::rb_tree<data_type, compare>::rb_tree(
    std::initializer_list<data_type> const& elem) {
  for (const auto& item : elem) {
    insert_data(item);
  }
}

template <typename data_type, typename compare>
s21::rb_tree<data_type, compare>& s21::rb_tree<data_type, compare>::operator=(
    rb_tree&& other) noexcept {
  if (this != &other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;
    compare_ = other.compare_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename data_type, typename compare>
data_type& s21::rb_tree<data_type, compare>::iterator::operator*() {
  if (ptr_) {
    return ptr_->data_;
  } else {
    static data_type default_value = data_type();
    return default_value;
  }
}
template <typename data_type, typename compare>
const data_type& s21::rb_tree<data_type, compare>::iterator::operator*() const {
  if (ptr_) {
    return ptr_->data_;
  } else {
    static data_type default_value = data_type();
    return default_value;
  }
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::iterator&
s21::rb_tree<data_type, compare>::iterator::operator=(const iterator& other) {
  ptr_ = other.ptr_;
  tree_ = other.tree_;
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::iterator&
s21::rb_tree<data_type, compare>::iterator::operator++() {
  if (ptr_->right_ != nullptr) {
    ptr_ = tree_->min_node(ptr_->right_);
  } else {
    node* parent = ptr_->parent_;
    while (parent != nullptr && ptr_ == parent->right_) {
      ptr_ = parent;
      parent = parent->parent_;
    }
    ptr_ = parent;
  }
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::iterator
s21::rb_tree<data_type, compare>::iterator::operator++(int) {
  iterator temp = *this;
  operator++();
  return temp;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::iterator&
s21::rb_tree<data_type, compare>::iterator::operator--() {
  if (ptr_->left_ != nullptr) {
    ptr_ = tree_->max_node(ptr_->left_);
  } else {
    node* parent = ptr_->parent_;
    while (parent != nullptr && ptr_ == parent->left_) {
      ptr_ = parent;
      parent = parent->parent_;
    }
    ptr_ = parent;
  }
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::iterator
s21::rb_tree<data_type, compare>::iterator::operator--(int) {
  iterator temp = *this;
  operator--();
  return temp;
}

template <typename data_type, typename compare>
const data_type& s21::rb_tree<data_type, compare>::const_iterator::operator*()
    const {
  if (ptr_) {
    return ptr_->data_;
  } else {
    static const data_type default_value = data_type();
    return default_value;
  }
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::const_iterator&
s21::rb_tree<data_type, compare>::const_iterator::operator=(
    const const_iterator& other) {
  ptr_ = other.ptr_;
  tree_ = other.tree_;
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::const_iterator&
s21::rb_tree<data_type, compare>::const_iterator::operator++() {
  if (ptr_->right_ != nullptr) {
    ptr_ = tree_->min_node(ptr_->right_);
  } else {
    node* parent = ptr_->parent_;
    while (parent != nullptr && ptr_ == parent->right_) {
      ptr_ = parent;
      parent = parent->parent_;
    }
    ptr_ = parent;
  }
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::const_iterator
s21::rb_tree<data_type, compare>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  operator++();
  return temp;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::const_iterator&
s21::rb_tree<data_type, compare>::const_iterator::operator--() {
  if (ptr_->left_ != nullptr) {
    ptr_ = tree_->max_node(ptr_->left_);
  } else {
    node* parent = ptr_->parent_;
    while (parent != nullptr && ptr_ == parent->left_) {
      ptr_ = parent;
      parent = parent->parent_;
    }
    ptr_ = parent;
  }
  return *this;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::const_iterator
s21::rb_tree<data_type, compare>::const_iterator::operator--(int) {
  const_iterator temp = *this;
  operator--();
  return temp;
}

template <typename data_type, typename compare>  // ++
typename s21::rb_tree<data_type, compare>::const_iterator
s21::rb_tree<data_type, compare>::find(const data_type& value) const {
  node* current = root_;
  while (current != nullptr) {
    if (compare_(value, current->data_)) {
      current = current->left_;
    } else if (compare_(current->data_, value)) {
      current = current->right_;
    } else {
      return const_iterator(current, this);
    }
  }
  return cend();
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::clear() {
  while (root_ != nullptr) {
    erase(iterator(root_, this));
  }
  this->size_ = 0;
}

template <typename data_type, typename compare>
std::pair<typename s21::rb_tree<data_type, compare>::iterator, bool>
s21::rb_tree<data_type, compare>::insert_data(const data_type& data) {
  node* current_node = root_;
  node* parent_node = nullptr;
  while (current_node != nullptr) {
    parent_node = current_node;
    if (compare_(data, current_node->data_)) {
      current_node = current_node->left_;
    } else if (compare_(current_node->data_, data)) {
      current_node = current_node->right_;
    } else {
      return std::make_pair(iterator(current_node, this), false);
    }
  }
  node* new_node = new node(data, nullptr);
  new_node->parent_ = parent_node;
  if (parent_node == nullptr) {
    root_ = new_node;
  } else if (!compare_(data, parent_node->data_)) {
    parent_node->right_ = new_node;
  } else {
    parent_node->left_ = new_node;
  }
  fix_violation(new_node);
  ++size_;
  return std::make_pair(iterator(new_node, this), true);
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::erase(iterator pos) {
  node* node_to_delete = pos.get_node();
  if (!node_to_delete) return;
  node* replacement_node = node_to_delete;
  node* child_node = nullptr;
  if (node_to_delete->left_ && node_to_delete->right_) {
    replacement_node = min_node(node_to_delete->right_);
  }
  if (replacement_node->left_) {
    child_node = replacement_node->left_;
  } else {
    child_node = replacement_node->right_;
  }
  if (child_node) {
    child_node->parent_ = replacement_node->parent_;
  }
  if (!replacement_node->parent_) {
    root_ = child_node;
  } else if (replacement_node == replacement_node->parent_->left_) {
    replacement_node->parent_->left_ = child_node;
  } else {
    replacement_node->parent_->right_ = child_node;
  }
  if (replacement_node != node_to_delete) {
    node_to_delete->data_ = replacement_node->data_;
  }

  if (replacement_node->color_ == black && child_node) {
    delete_fix(child_node);
  }
  delete replacement_node;
  --size_;
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::swap(rb_tree& other) noexcept {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(compare_, other.compare_);
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::merge(rb_tree& other) {
  if (this == &other) return;
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert_data(*it);
  }
  other.clear();
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::node*
s21::rb_tree<data_type, compare>::copy_tree(node* src) {
  if (src == nullptr) {
    return nullptr;
  }
  std::stack<node*> src_stack, copy_stack;
  src_stack.push(src);
  node* new_root = new node(src->data_, nullptr);
  copy_stack.push(new_root);
  while (!src_stack.empty()) {
    node* src_node = src_stack.top();
    node* copy_node = copy_stack.top();
    src_stack.pop();
    copy_stack.pop();
    if (src_node->right_ != nullptr) {
      copy_node->right_ = new node(src_node->right_->data_, copy_node);
      copy_stack.push(copy_node->right_);
      src_stack.push(src_node->right_);
    }
    if (src_node->left_ != nullptr) {
      copy_node->left_ = new node(src_node->left_->data_, copy_node);
      copy_stack.push(copy_node->left_);
      src_stack.push(src_node->left_);
    }
  }
  return new_root;
}

template <typename data_type, typename compare>  // ++
typename s21::rb_tree<data_type, compare>::iterator
s21::rb_tree<data_type, compare>::find(const data_type& value) {
  node* current = root_;
  while (current != nullptr) {
    if (compare_(value, current->data_)) {
      current = current->left_;
    } else if (compare_(current->data_, value)) {
      current = current->right_;
    } else {
      return iterator(current, this);
    }
  }
  return end();
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::node*
s21::rb_tree<data_type, compare>::max_node(node* node_curr) const {
  while (node_curr->right_ != nullptr) {
    node_curr = node_curr->right_;
  }
  return node_curr;
}

template <typename data_type, typename compare>
typename s21::rb_tree<data_type, compare>::node*
s21::rb_tree<data_type, compare>::min_node(node* node_curr) const {
  while (node_curr->left_ != nullptr) {
    node_curr = node_curr->left_;
  }
  return node_curr;
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::rotate_left(node* node_curr) {
  node* right_child = node_curr->right_;
  node_curr->right_ = right_child->left_;
  if (node_curr->right_) {
    node_curr->right_->parent_ = node_curr;
  }
  right_child->parent_ = node_curr->parent_;
  if (!node_curr->parent_) {
    root_ = right_child;
  } else if (node_curr == node_curr->parent_->left_) {
    node_curr->parent_->left_ = right_child;
  } else {
    node_curr->parent_->right_ = right_child;
  }
  right_child->left_ = node_curr;
  node_curr->parent_ = right_child;
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::rotate_right(node* node_curr) {
  node* left_child = node_curr->left_;
  node_curr->left_ = left_child->right_;
  if (node_curr->left_ != nullptr) {
    node_curr->left_->parent_ = node_curr;
  }
  left_child->parent_ = node_curr->parent_;
  if (node_curr->parent_ == nullptr) {
    root_ = left_child;
  } else if (node_curr == node_curr->parent_->left_) {
    node_curr->parent_->left_ = left_child;
  } else {
    node_curr->parent_->right_ = left_child;
  }
  left_child->right_ = node_curr;
  node_curr->parent_ = left_child;
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::fix_violation(node* node_curr) {
  while (node_curr != root_ && node_curr->parent_->color_ == red) {
    node* parent = node_curr->parent_;
    node* grandparent = parent->parent_;
    if (parent == grandparent->left_) {
      node* uncle = grandparent->right_;
      if (uncle != nullptr && uncle->color_ == red) {
        grandparent->color_ = red;
        parent->color_ = black;
        uncle->color_ = black;
        node_curr = grandparent;
      } else {
        if (node_curr == parent->right_) {
          rotate_left(parent);
          node_curr = parent;
          parent = node_curr->parent_;
        }
        rotate_right(grandparent);
        std::swap(parent->color_, grandparent->color_);
        node_curr = parent;
      }
    } else {
      node* uncle = grandparent->left_;
      if (uncle != nullptr && uncle->color_ == red) {
        grandparent->color_ = red;
        parent->color_ = black;
        uncle->color_ = black;
        node_curr = grandparent;
      } else {
        if (node_curr == parent->left_) {
          rotate_right(parent);
          node_curr = parent;
          parent = node_curr->parent_;
        }
        rotate_left(grandparent);
        std::swap(parent->color_, grandparent->color_);
        node_curr = parent;
      }
    }
  }

  root_->color_ = black;
}

template <typename data_type, typename compare>
void s21::rb_tree<data_type, compare>::delete_fix(node* node_curr) {
  while (node_curr != root_ && node_curr->color_ == black) {
    if (node_curr == node_curr->parent_->left_) {
      node* sibling = node_curr->parent_->right_;
      if (sibling->color_ == red) {
        sibling->color_ = black;
        node_curr->parent_->color_ = red;
        rotate_left(node_curr->parent_);
        sibling = node_curr->parent_->right_;
      }
      if (sibling->left_->color_ == black && sibling->right_->color_ == black) {
        sibling->color_ = red;
        node_curr = node_curr->parent_;
      } else {
        if (sibling->right_->color_ == black) {
          sibling->left_->color_ = black;
          sibling->color_ = red;
          rotate_right(sibling);
          sibling = node_curr->parent_->right_;
        }
        sibling->color_ = node_curr->parent_->color_;
        node_curr->parent_->color_ = black;
        sibling->right_->color_ = black;
        rotate_left(node_curr->parent_);
        node_curr = root_;
      }
    } else {
      node* sibling = node_curr->parent_->left_;
      if (sibling->color_ == red) {
        sibling->color_ = black;
        node_curr->parent_->color_ = red;
        rotate_right(node_curr->parent_);
        sibling = node_curr->parent_->left_;
      }
      if (sibling->left_->color_ == black && sibling->right_->color_ == black) {
        sibling->color_ = red;
        node_curr = node_curr->parent_;
      } else {
        if (sibling->left_->color_ == black) {
          sibling->right_->color_ = black;
          sibling->color_ = red;
          rotate_left(sibling);
          sibling = node_curr->parent_->left_;
        }
        sibling->color_ = node_curr->parent_->color_;
        node_curr->parent_->color_ = black;
        sibling->left_->color_ = black;
        rotate_right(node_curr->parent_);
        node_curr = root_;
      }
    }
  }
  node_curr->color_ = black;
}

#endif