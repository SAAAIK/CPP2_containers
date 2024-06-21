#ifndef S21_list
#define S21_list

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 protected:
  struct node;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list() : size_(0), head_(nullptr), tail_(nullptr) {}
  list(size_type size_);
  list(const list &other);
  list(list &&other) noexcept;
  list(std::initializer_list<value_type> const &elem);
  ~list() noexcept { clear(); }

  reference operator[](size_type ind);

  list &operator=(list &&other) noexcept;

  class iterator;
  class const_iterator;

  iterator begin() {
    return iterator(this->head_ ? this->head_ : nullptr, this);
  }
  iterator end() { return iterator(nullptr, this); }
  // iterator end() { return iterator(this->get_current(), this); }
  const_iterator cbegin() const {
    return const_iterator(this->head_ ? this->head_ : nullptr, this);
  }
  const_iterator cend() const { return const_iterator(nullptr, this); }

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void merge(list &other);
  void splice(iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  bool empty() const noexcept { return head_ == nullptr; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::allocator_traits<std::allocator<node>>::max_size(
        std::allocator<node>());
  }

  void push_back(const_reference value);
  void push_front(const_reference value);

  void pop_back();
  void pop_front();

  const_reference front() const;
  const_reference back() const;
  node *get_current() { return *this->current_; }

  void swap(list &other) noexcept;

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  // вспомогательные методы ----------------------------------------------
  void print();

 protected:
  struct node {
    value_type data_;
    node *next_;
    node *prev_;
    node(value_type data_ = value_type(), node *next_ = nullptr,
         node *prev_ = nullptr) {
      this->data_ = data_;
      this->next_ = next_;
      this->prev_ = prev_;
    }
  };

  size_type size_;
  node *head_;
  node *tail_;
};  //---------------------------------------------------------------

template <typename T>
class list<T>::iterator {
 public:
  iterator() : current_(nullptr), p_list_(nullptr) {}
  iterator(node *current, list *p_list) : current_(current), p_list_(p_list) {}
  iterator(const iterator &other)
      : current_(other.current_), p_list_(other.p_list_) {}

  T &operator*() { return current_->data_; }
  node *get_node() const { return current_; }
  iterator &operator++() {
    if (current_ != nullptr) current_ = current_->next_;
    return *this;
  }

  iterator operator++(int) {
    iterator temp = *this;
    operator++();
    return temp;
  }

  iterator &operator--() {
    if (current_ != nullptr && current_->prev_ != nullptr) {
      current_ = current_->prev_;
    }
    return *this;
  }

  iterator operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
  }

  iterator &operator=(const iterator &other) {
    if (this != &other) current_ = other.current_;
    return *this;
  }

  bool operator==(const iterator &other) { return current_ == other.current_; }
  bool operator!=(const iterator &other) { return current_ != other.current_; }

  node *get_current() { return current_; }

 protected:
  node *current_;
  list *p_list_;
};  //----------------------------------------------------------------

template <typename T>
class list<T>::const_iterator {
 public:
  const_iterator() : current_(nullptr), p_list_(nullptr) {}
  const_iterator(const node *current, const list *p_list)
      : current_(current), p_list_(p_list) {}
  const_iterator(const const_iterator &other)
      : current_(other.current_), p_list_(other.p_list_) {}

  const T &operator*() const { return current_->data_; }

  const_iterator &operator++() {
    if (current_ != nullptr && current_->next_ != nullptr)
      current_ = current_->next_;
    return *this;
  }

  const_iterator operator++(int) {
    const_iterator temp = *this;
    operator++();
    return temp;
  }

  const_iterator &operator--() {
    if (current_ != nullptr && current_->prev_ != nullptr) {
      current_ = current_->prev_;
    }
    return *this;
  }

  const_iterator &operator--(int) {
    const_iterator temp = *this;
    operator--();
    return temp;
  }

  const_iterator &operator=(const const_iterator &other) {
    if (this != &other) current_ = other.current_;
    return *this;
  }

  bool operator==(const const_iterator &other) const {
    return current_ == other.current_;
  }
  bool operator!=(const const_iterator &other) const {
    return !(current_ == other.current_);
  }

  node *get_current() { return current_; }

 protected:
  const node *current_;
  const list *p_list_;
};

}  // namespace s21

// конструкторы___________________________________________________________

template <typename T>
s21::list<T>::list(size_type size) : list() {
  if (size == 0) {
    throw std::out_of_range("Size must be greater than zero");
  } else {
    for (size_type i = 0; i < size; i++) {
      push_back(value_type{});
    }
  }
}

template <typename T>
s21::list<T>::list(const list &other) : list() {
  if (this != &other) {
    node *temp = other.head_;
    while (temp != nullptr) {
      push_back(temp->data_);
      temp = temp->next_;
    }
  }
}

template <typename T>
s21::list<T>::list(list &&other) noexcept {
  this->size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
s21::list<T>::list(std::initializer_list<T> const &elem) : list() {
  for (const auto &elem : elem) {
    push_back(elem);
  }
}

// операторы
// --------------------------------------------------------------------------

template <typename T>
T &s21::list<T>::operator[](size_type ind) {
  node *temp = head_;
  for (size_type i = 0; i < ind && temp != nullptr; i++) {
    temp = temp->next_;
  }
  return temp->data_;
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(list &&other) noexcept {
  if (this != &other) {
    clear();
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// методы
// -----------------------------------------------------------------------------

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  node *new_node = new node(value);
  if (!new_node) {
    throw std::bad_alloc();
  }
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  node *new_node = new node(value);
  if (!new_node) {
    throw std::bad_alloc();
  }
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
    ++this->size_;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
    ++this->size_;
  }
}

template <typename T>
void s21::list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Cannot pop from back an empty list");
  } else {
    node *temp = tail_;
    tail_ = tail_->prev_;
    if (tail_) {
      tail_->next_ = nullptr;
      --this->size_;
    } else {
      head_ = nullptr;
      --this->size_;
    }
    delete temp;
  }
}

template <typename T>
void s21::list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Cannot pop front from an empty list");
  } else {
    node *temp = head_;
    head_ = head_->next_;
    if (head_) {
      head_->prev_ = nullptr;
      --this->size_;
    } else {
      tail_ = nullptr;
      --this->size_;
    }
    delete temp;
  }
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Cannot get front from an empty list");
  }
  return (const_reference)head_->data_;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Cannot get const_back from an empty list");
  }
  return (const_reference)tail_->data_;
}

template <typename T>
void s21::list<T>::swap(list &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void s21::list<T>::clear() noexcept {
  while (!empty()) {
    node *temp = this->head_;
    head_ = head_->next_;
    delete temp;
  }
  this->size_ = 0;
  this->head_ = NULL;
  this->tail_ = NULL;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  node *current = this->head_;
  iterator it = this->begin();
  iterator end_it = this->end();

  if (it == pos) {
    push_front(value);
    --it;
  } else if (pos == end_it) {
    push_back(value);
    --it;
  } else {
    --pos;
    node *temp = new node(value);
    while (it != pos) {
      ++it;
      current = current->next_;
    }
    temp->next_ = current->next_;
    temp->prev_ = current;
    current->next_ = temp;
    temp->next_->prev_ = temp;
    ++it;
    ++this->size_;
  }
  return it;
}

template <typename T>
void s21::list<T>::reverse() {
  node *current = this->head_;
  node *prev = nullptr;
  node *next = nullptr;
  while (current != nullptr) {
    next = current->next_;

    current->next_ = prev;
    current->prev_ = next;

    prev = current;
    current = next;
  }
  this->tail_ = this->head_;
  this->head_ = prev;
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    pop_back();
  } else {
    node *prev_node = pos.get_current()->prev_;
    node *next_node = pos.get_current()->next_;
    prev_node->next_ = next_node;
    if (next_node != nullptr) {
      next_node->prev_ = prev_node;
    }
    delete pos.get_current();
    --size_;
  }
}

template <typename T>
void s21::list<T>::merge(list &other) {
  iterator it = this->begin();
  while (!other.empty()) {
    value_type value = std::move(other.front());
    while (it != this->end() && *it < value) {
      ++it;
    }
    other.pop_front();
    if (it != this->end()) {
      this->insert(it, std::move(value));
    } else {
      this->push_back(std::move(value));
    }
  }
}
template <typename T>
void s21::list<T>::unique() {
  if (!this->empty()) {
    for (iterator it_last = begin(); it_last != end();) {
      iterator it_next = it_last;
      ++it_next;
      if (it_next.get_current() == nullptr) {
        return;
      } else if (*it_last == *it_next) {
        erase(it_next);
      } else {
        ++it_last;
      }
    }
  }
}

template <typename T>
void s21::list<T>::sort() {
  if (this->size_ <= 1) return;

  int swapped = 1;
  while (swapped) {
    swapped = 0;
    node *current = this->head_;
    while (current != nullptr && current->next_ != nullptr) {
      if (current->data_ > current->next_->data_) {
        T temp = current->data_;
        current->data_ = current->next_->data_;
        current->next_->data_ = temp;
        swapped = 1;
      }
      current = current->next_;
    }
  }
}

template <class T>
void s21::list<T>::splice(iterator pos, list &other) {
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
  }
}

// вспомогательная функция
template <typename T>
void s21::list<T>::print() {
  node *current = head_;
  while (current != nullptr) {
    std::cout << current->data_ << " ";
    current = current->next_;
  }
  std::cout << std::endl;
  std::cout << "size of list =  " << size_ << std::endl;
  std::cout << std::endl;
}

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(iterator pos,
                                                          Args &&...args) {
  int shift = 0;
  for (auto &arg : {args...}) {
    insert(pos, arg);
    shift++;
  }
  iterator buf = pos;
  for (int i = 0; i < shift; i++) --buf;
  return buf;
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  auto it = end();
  ((insert(it, std::forward<Args>(args)), --it), ...);
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  auto it = begin();
  ((insert(it, std::forward<Args>(args)), --it), ...);
}

#endif