#ifndef S21_ARRAY
#define S21_ARRAY

#include <stddef.h>  // for size_t

#include <iterator>
#include <memory>
#include <stdexcept>  // for exceptions

namespace s21 {
template <typename T, size_t N = 0>  // По умолчанию размер = 0
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;
  using allocator_type = std::allocator<T>;

  array();  // Конструктор по умолчанию
  array(std::initializer_list<value_type> const
            &items);      // Инициализирующий список
  array(const array &a);  // Конструктор копирования
  array(array &&a);       // Конструктор перемещения
  ~array();               // Деструктор
  array &operator=(const array &a);  // Оператор присваивания
  array &operator=(array &&a);       // Оператор перемещения
  reference at(size_type pos);       // Значение по индексу
  reference operator[](size_type pos);  // Оператор []
  const_reference front();              // Первый элемент
  const_reference back();               // Последний элемент
  pointer data();  // Получение указателя на 1 элемент
  iterator begin();         // Начало
  iterator end();           // Конец
  void swap(array &other);  // Обмен значений
  void fill(const_reference value);  // Заполнение заданным значением
  size_type max_size();  // Максимальный размер

  bool empty();      // Пустой ли массив
  size_type size();  // Размер

 protected:
  pointer data_;
  allocator_type allocator_;  // Аллокатор
  size_type count_;           // Размер
};
}  // namespace s21

template <typename T, size_t N>
s21::array<T, N>::array() : data_(nullptr), count_(0) {
  // Инициализируем данные аллокатором по умолчанию
  if (N > 0) {
    data_ = allocator_.allocate(N);  // Выделяем память, если размер N больше 0
    count_ = N;
    std::uninitialized_fill_n(
        data_, N,
        T());  // Инициализируем диапазон элементов с заданным значением
  }
}

template <typename T, size_t N>
s21::array<T, N>::array(std::initializer_list<value_type> const &items) {
  count_ = items.size();
  data_ = allocator_.allocate(count_);
  std::uninitialized_copy(items.begin(), items.end(), data_);
}

template <typename T, size_t N>
s21::array<T, N>::array(const array &a) {
  this->count_ = a.count_;
  data_ = allocator_.allocate(this->count_);
  std::uninitialized_copy(a.data_, a.data_ + a.count_, data_);
}

template <typename T, size_t N>
s21::array<T, N>::array(array &&a)
    : data_(a.data_), allocator_(std::move(a.allocator_)), count_(a.count_) {
  a.data_ = nullptr;
  a.count_ = 0;
}

template <typename T, size_t N>
s21::array<T, N>::~array() {
  if (data_ != nullptr) {
    // Уничтожаем содержимое каждого элемента
    for (size_t i = 0; i < count_; i++) {
      // allocator_.destroy(data_ + i);
      data_[i].~T();
    }
    // Освобождаем выделенную память
    allocator_.deallocate(data_, count_);
  }
}

template <typename T, size_t N>
s21::array<T, N> &s21::array<T, N>::operator=(const array<T, N> &a) {
  if (this != &a) {  // Проверка на самоприсваивание
    if (data_) {
      // Если уже есть данные, сначала уничтожаем их
      for (size_t i = 0; i < count_; i++) {
        // allocator_.destroy(data_ + i);
        data_[i].~T();
      }
      allocator_.deallocate(data_, count_);
    }
    // Выделяем новую память и копируем элементы
    count_ = a.count_;
    data_ = allocator_.allocate(count_);
    std::uninitialized_copy(a.data_, a.data_ + count_, data_);
  }
  return *this;
}

template <typename T, size_t N>
s21::array<T, N> &s21::array<T, N>::operator=(array<T, N> &&a) {
  if (this != &a) {  // Проверка на самоприсваивание
    if (data_) {
      // Уничтожаем и освобождаем текущие ресурсы
      for (size_t i = 0; i < count_; i++) {
        // allocator_.destroy(data_ + i);
        data_[i].~T();
      }
      allocator_.deallocate(data_, count_);
    }

    // Переносим ресурсы
    data_ = a.data_;
    count_ = a.count_;
    allocator_ = std::move(a.allocator_);

    // Обнуляем исходный объект
    a.data_ = nullptr;
    a.count_ = 0;
  }
  return *this;
}

template <typename T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::at(size_type pos) {
  if (pos >= count_) {  // Проверяем, не выходит ли индекс за пределы массива
    throw std::out_of_range(
        "Index out of range");  // Выброс исключения, если индекс вне диапазона
  }
  return data_[pos];  // Возвращаем ссылку на элемент
}

template <typename T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    size_type pos) {
  return data_[pos];  // Возвращает ссылку на элемент без проверки границ
}

template <typename T, size_t N>
typename s21::array<T, N>::const_reference s21::array<T, N>::front() {
  return data_[0];  // Возвращает значение первый элемент
}

template <typename T, size_t N>
typename s21::array<T, N>::const_reference s21::array<T, N>::back() {
  return data_[count_ - 1];  // Возвращает занчение последний элемент
}

template <typename T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::data() {
  return begin();  // Просто возвращает итератор начала
}

template <typename T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::begin() {
  return data_;  // Возвращает итератор начала массива данных
}

template <typename T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::end() {
  return data_ + count_;  // Возвращает итератор конца массива данных
}

template <typename T, size_t N>
void s21::array<T, N>::swap(array &other) {
  std::swap(data_, other.data_);  // Обмениваем указатели на данные
  std::swap(count_, other.count_);  // Обмениваем количество элементов
}

template <typename T, size_t N>
void s21::array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < count_; ++i) {
    data_[i] = value;  // Заполняем каждый элемент заданным значением
  }
}
template <typename T, size_t N>
typename s21::array<T, N>::size_type s21::array<T, N>::max_size() {
  return count_;
}

template <typename T, size_t N>
bool s21::array<T, N>::empty() {
  return count_ == 0;  // Возвращает true, если количество элементов равно 0
}

template <typename T, size_t N>
typename s21::array<T, N>::size_type s21::array<T, N>::size() {
  return count_;  // Возвращает текущее количество элементов
}

#endif
