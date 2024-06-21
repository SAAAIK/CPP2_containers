#ifndef S21_STACK
#define S21_STACK

#include <iostream>

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  stack &operator=(stack &&s);

  ~stack();

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  typedef struct node {
    value_type data_;
    node *ptr_prev_;

    node(value_type data) : data_(data), ptr_prev_(nullptr) {}
  } node;

  node *tail_;
  size_type count_;
};
}  // namespace s21

template <typename T>
s21::stack<T>::stack() : tail_(nullptr), count_(0) {}

template <typename T>
s21::stack<T>::stack(std::initializer_list<value_type> const &items)
    : tail_(nullptr), count_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
s21::stack<T>::stack(const s21::stack<T> &s) : tail_(nullptr), count_(0) {
  node *current = s.tail_;
  stack<T> temp_stack;
  while (current != nullptr) {
    temp_stack.push(current->data_);
    current = current->ptr_prev_;
  }

  while (!temp_stack.empty()) {
    this->push(temp_stack.top());
    temp_stack.pop();
  }
}
template <typename T>
s21::stack<T>::stack(s21::stack<T> &&s) : tail_(s.tail_), count_(s.count_) {
  s.tail_ = nullptr;
  s.count_ = 0;
}

template <typename T>
s21::stack<T> &s21::stack<T>::operator=(s21::stack<T> &&s) {
  if (this != &s) {
    while (!empty()) {
      pop();
    }
    tail_ = s.tail_;
    count_ = s.count_;
    s.tail_ = nullptr;
    s.count_ = 0;
  }
  return *this;
}

template <typename T>
s21::stack<T>::~stack() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
bool s21::stack<T>::empty() {
  return count_ == 0;
}

template <typename T>
typename s21::stack<T>::size_type s21::stack<T>::size() {
  return count_;
}

template <typename T>
typename s21::stack<T>::const_reference s21::stack<T>::top() {
  if (empty()) {
    throw std::logic_error("Cannot get top from an empty stack");
  }
  return tail_->data_;
}

template <typename T>
void s21::stack<T>::push(const_reference value) {
  node *temp = new node(value);
  if (!tail_) {
    tail_ = temp;
  } else {
    temp->ptr_prev_ = tail_;
    tail_ = temp;
  }
  count_++;
}

template <typename T>
void s21::stack<T>::pop() {
  if (empty()) {
    throw std::logic_error("Cannot pop from an empty stack");
  }
  node *temp = tail_->ptr_prev_;
  delete tail_;
  tail_ = temp;
  count_--;
}

template <typename T>
void s21::stack<T>::swap(stack &other) {
  std::swap(tail_, other.tail_);
  std::swap(count_, other.count_);
}

template <typename T>
template <typename... Args>
void s21::stack<T>::insert_many_front(Args &&...args) {
  (push(args), ...);
}

#endif