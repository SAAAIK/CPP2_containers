#ifndef S21_VECTOR
#define S21_VECTOR

#include <stddef.h>  // для size_t

#include <iterator>
#include <memory>
#include <stdexcept>  // для исключений

namespace s21 {
template <typename T>
class vector {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;
  using allocator_type = std::allocator<T>;

 public:
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);

  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector &operator=(const vector &v);
  vector &operator=(vector &&v);

  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);

  ///////
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  ///////

  void push_back(const_reference value);
  void pop_back();
  size_type max_size();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  size_type size();  // Размер
  iterator begin();  // Начало
  iterator end();

 private:
  size_type capacity_;

  pointer data_;
  allocator_type allocator_;  // Аллокатор
  size_type count_;           // Размер
};
}  // namespace s21

//////
template <typename T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  return data_[pos];  // Возвращает ссылку на элемент без проверки границ
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::front() {
  return data_[0];  // Возвращает значение первый элемент
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::back() {
  return data_[count_ - 1];  // Возвращает занчение последний элемент
}

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (pos >= count_) {
    throw std::out_of_range("Index out of range in vector::at");
  }
  return data_[pos];
}

///////
template <typename T>
s21::vector<T>::vector() : capacity_(0), data_(nullptr), count_(0) {}

template <typename T>
s21::vector<T>::vector(size_type n) {
  capacity_ = n;
  this->count_ = n;
  this->data_ =
      this->allocator_.allocate(n);  // Выделяем память для n элементов
  for (size_type i = 0; i < n; i++) {
    new (data_ + i) T();  // Использование placement new для создания объектов
  }
}

template <typename T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items) {
  count_ = items.size();
  data_ = allocator_.allocate(count_);
  std::uninitialized_copy(items.begin(), items.end(), data_);
  capacity_ = items.size();
}

template <typename T>
s21::vector<T>::vector(const vector &v) {
  this->count_ = v.count_;
  data_ = allocator_.allocate(this->count_);
  std::uninitialized_copy(v.data_, v.data_ + v.count_, data_);
  capacity_ = v.capacity_;
}

template <typename T>
s21::vector<T>::vector(vector &&v) {
  data_ = v.data_;
  allocator_ = std::move(v.allocator_);
  count_ = v.count_;
  v.data_ = nullptr;
  v.count_ = 0;

  capacity_ = v.capacity_;
  v.capacity_ = 0;
}

template <typename T>
s21::vector<T>::~vector() {
  if (data_ != nullptr) {
    // Уничтожаем содержимое каждого элемента
    for (size_type i = 0; i < count_; i++) {
      // allocator_.destroy(data_ + i);
      data_[i].~T();
    }
    // Освобождаем выделенную память
    allocator_.deallocate(data_, count_);
  }
  capacity_ = 0;
}

template <typename T>
s21::vector<T> &s21::vector<T>::operator=(const vector<T> &v) {
  if (this != &v) {  // Проверка на самоприсваивание
    if (data_) {
      // Если уже есть данные, сначала уничтожаем их
      for (size_type i = 0; i < count_; i++) {
        // allocator_.destroy(data_ + i);
        data_[i].~T();
      }
      allocator_.deallocate(data_, count_);
    }
    // Выделяем новую память и копируем элементы
    count_ = v.count_;
    data_ = allocator_.allocate(count_);
    std::uninitialized_copy(v.data_, v.data_ + count_, data_);
    capacity_ = v.capacity_;  // Копирование capacity из v
  }
  return *this;
}

template <typename T>
s21::vector<T> &s21::vector<T>::operator=(vector<T> &&v) {
  if (this != &v) {  // Проверка на самоприсваивание
    if (data_) {
      // Уничтожаем и освобождаем текущие ресурсы
      for (size_type i = 0; i < count_; i++) {
        // allocator_.destroy(data_ + i);
        data_[i].~T();
      }
      allocator_.deallocate(data_, count_);
    }

    // Переносим ресурсы
    data_ = v.data_;
    count_ = v.count_;
    allocator_ = std::move(v.allocator_);

    // Обнуляем исходный объект
    v.data_ = nullptr;
    v.count_ = 0;
    capacity_ = v.capacity_;  // Перенос capacity
    v.capacity_ = 0;          // Обнуление capacity у v
  }
  return *this;
}

template <typename T>
void s21::vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    pointer new_data = allocator_.allocate(size);
    std::uninitialized_copy(std::make_move_iterator(data_),
                            std::make_move_iterator(data_ + count_), new_data);
    for (size_type i = 0; i < count_; ++i) {
      data_[i].~T();
    }
    if (data_) {
      allocator_.deallocate(data_, capacity_);
    }
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void s21::vector<T>::shrink_to_fit() {
  if (this->size() == 0) capacity_ = 0;
  if (capacity_ > count_) {
    pointer new_data = allocator_.allocate(
        count_);  // Выделение памяти точно под количество элементов

    for (size_type i = 0; i < count_; ++i) {
      new_data[i] = std::move(data_[i]);  // Присваивание элементов
    }

    for (size_type i = 0; i < count_; ++i) {
      data_[i].~T();
    }
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = count_;  // Новая емкость равна количеству элементов
  }
}

template <typename T>
void s21::vector<T>::clear() {
  // Уничтожаем все элементы в векторе
  for (size_type i = 0; i < count_; i++) {
    data_[i].~T();
  }
  // Устанавливаем количество элементов вектора в 0
  count_ = 0;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  size_type index = pos - begin();

  if (count_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  iterator new_pos = begin() + index;

  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++count_;

  return new_pos;
}
template <typename T>
void s21::vector<T>::erase(iterator pos) {
  // Проверяем, действителен ли итератор
  if (pos < data_ || pos >= data_ + count_) {
    throw std::out_of_range("Iterator out of bounds in erase()");
  }

  // Рассчитываем индекс удаляемого элемента
  size_type index = pos - data_;

  // Вызываем деструктор для удаляемого элемента
  (data_ + index)->~T();

  // Сдвигаем все последующие элементы на одну позицию влево
  for (size_type i = index; i < count_ - 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }

  // Уничтожаем последний элемент, теперь когда он был перемещен
  (data_ + count_ - 1)->~T();

  // Уменьшаем количество элементов в векторе
  --count_;
}

template <typename T>
void s21::vector<T>::push_back(const_reference value) {
  if (count_ >= capacity_) {
    // Если текущая емкость достигнута, увеличиваем её
    reserve(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  // Конструируем новый элемент на месте последнего с использованием
  // плейсмент-нью
  new (data_ + count_) T(value);
  // Увеличиваем количество элементов в векторе
  count_++;
}

template <typename T>
void s21::vector<T>::pop_back() {
  if (count_ != 0) {
    // Вызываем деструктор для последнего элемента вектора
    data_[count_ - 1].~T();
    // Уменьшаем количество элементов в векторе
    count_--;
  }
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void s21::vector<T>::swap(vector &other) {
  // Использование std::swap для обмена значениями
  std::swap(data_, other.data_);
  std::swap(capacity_, other.capacity_);
  std::swap(count_, other.count_);
  std::swap(allocator_, other.allocator_);  // Только если это безопасно
}

template <typename T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args &&...args) {
  // Определяем индекс вставки
  size_type index = pos - this->begin();
  // Создаем временный вектор, чтобы удобно использовать реализованные методы
  vector<T> temp_vector({args...});
  size_type temp_size = temp_vector.size();
  // Расширяем вектор, если необходимо
  reserve(capacity_ + temp_size);

  // Начало данных для вставки
  pointer temp_data = temp_vector.data();

  // Итератор (указатель) позиции вставки
  iterator result = nullptr;
  for (size_type i = temp_size; i > 0; i--) {
    // Поочередно вставляем с конца вектора темп значения в одну и ту же позиции
    // (в функции инсерт уже реализован сдвиг и выделние памяти)
    iterator insert_pos = this->data() + index;
    result = insert(insert_pos, temp_data[i - 1]);
  }
  // В итоге, в резалт хранится итератор на вставленный элемент
  return result;
}

template <typename T>
template <typename... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  // оператор fold expression, который вызывает функцию push_back для
  // каждого аргумента в пакете аргументов args
  (push_back(args), ...);
}

///////////////////
template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
  return count_;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::data() {
  return begin();  // Просто возвращает итератор начала
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
  return data_ + count_;  // Возвращает итератор конца массива данных
}
template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
  return data_;  // Возвращает итератор начала массива данных
}

#endif