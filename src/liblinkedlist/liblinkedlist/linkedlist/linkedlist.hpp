#pragma once
#include <iostream>
namespace linkedlist {
template <typename T> class LinkedList {

private:
  struct Node {
    T data;
    Node *prev;
    Node *next;
  };
  Node *head;
  Node *tail;
  size_t size_;

public:
  // Коснтрукторы, деструктор, специальные методы------------------------

  // Конструкторы по умолчанию
  LinkedList() : head{nullptr}, tail{nullptr}, size_{0} {}

  // Конструктор по диапазону
  template <typename It>
  LinkedList(It begin, It end) : head(nullptr), tail(nullptr), size_(0) {
    for (auto it = begin; it != end; ++it) {
      push_back(*it);
    }
  }

  // Конструктор по списку инициализации
  LinkedList(std::initializer_list<T> list)
      : head(nullptr), tail(nullptr), size_(0) {
    for (const T &elem : list) {
      push_back(elem);
    }
  }

  //  Деструктор
  ~LinkedList() { clear(); }

  // Копирующий конструктор
  LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), size_(0) {
    for (Node *currentNode = other.head; currentNode != nullptr;
         currentNode = currentNode->next) {
      push_back(currentNode->data);
    }
  }

  // Перемещающий конструктор
  LinkedList(LinkedList &&other) noexcept
      : head(other.head), tail(other.tail), size_(other.size_) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }

  // Копирующий оператор присваивания
  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      clear();
      for (Node *currentNode = other.head; currentNode != nullptr;
           currentNode = currentNode->next) {
        push_back(currentNode->data);
      }
    }
    return *this;
  }

  // Перемещающий оператор присваивания
  LinkedList &operator=(LinkedList &&other) noexcept {
    if (this != &other) {
      clear();
      head = other.head;
      tail = other.tail;
      size_ = other.size_;

      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // ----------------------------------------------------------------------
  // front, back — возвращают ссылку на первый и последний элемент
  // соответственно
  T &front() {
    if (head == nullptr) {
      throw std::out_of_range("front() called on an empty list");
    }
    return head->data;
  }

  const T &front() const {
    if (head == nullptr) {
      throw std::out_of_range("front() called on an empty list");
    }
    return head->data;
  }

  T &back() {
    if (tail == nullptr) {
      throw std::out_of_range("back() called on an empty list");
    }
    return tail->data;
  }
  const T &back() const {
    if (tail == nullptr) {
      throw std::out_of_range("back() called on an empty list");
    }
    return tail->data;
  }

  // push_front, push_back — добавляют элемент в начало и в конец вектора
  // соответственно
  void push_front(const T &data) {
    Node *newNode = new Node{data, nullptr, head};
    if (head == nullptr) {
      tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
    }
    head = newNode;

    ++size_;
  }

  void push_front(T &&data) {
    Node *newNode = new Node{std::move(data), nullptr, head};
    if (head == nullptr) {
      tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
    }
    head = newNode;

    ++size_;
  }

  void push_back(const T &data) {
    Node *newNode = new Node{data, tail, nullptr};
    if (head == nullptr) {
      head = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
    }
    tail = newNode;

    ++size_;
  }

  void push_back(T &&data) {
    Node *newNode = new Node{std::move(data), tail, nullptr};
    if (head == nullptr) {
      head = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
    }
    tail = newNode;

    ++size_;
  }

  // Итераторы------------------------------------------------------------
  // Неконстантный итератор
  class Iterator {
  private:
    Node *current_;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    Iterator(Node *current) : current_(current) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    Iterator &operator++() {
      if (current_ != nullptr) {
        current_ = current_->next;
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator &operator--() {
      if (current_ != nullptr) {
        current_ = current_->prev;
      }
      return *this;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const Iterator &other) const {
      return current_ != other.current_;
    }
  };

  // Константный итератор
  class ConstIterator {
  private:
    const Node *current_;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::bidirectional_iterator_tag;

    ConstIterator(const Node *current) : current_(current) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    ConstIterator &operator++() {
      if (current_ != nullptr) {
        current_ = current_->next;
      }
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    ConstIterator &operator--() {
      if (current_ != nullptr) {
        current_ = current_->prev;
      }
      return *this;
    }

    ConstIterator operator--(int) {
      ConstIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ConstIterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ConstIterator &other) const {
      return current_ != other.current_;
    }
  };

  class ReverseIterator {
  private:
    Node *current_;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    ReverseIterator(Node *current) : current_(current) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    ReverseIterator &operator++() {
      if (current_ != nullptr) {
        current_ = current_->prev;
      }
      return *this;
    }

    ReverseIterator operator++(int) {

      ReverseIterator temp = *this;
      --(*this);
      return temp;
    }

    ReverseIterator &operator--() {

      if (current_ != nullptr) {
        current_ = current_->next;
      }
      return *this;
    }

    ReverseIterator operator--(int) {

      ReverseIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const ReverseIterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ReverseIterator &other) const {
      return current_ != other.current_;
    }
  };

  // Константный итератор
  class ConstReverseIterator {
  private:
    const Node *current_;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::bidirectional_iterator_tag;

    ConstReverseIterator(const Node *current) : current_(current) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    ConstReverseIterator &operator++() {
      if (current_ != nullptr) {
        current_ = current_->prev;
      }
      return *this;
    }

    ConstReverseIterator operator++(int) {
      ConstReverseIterator temp = *this;
      --(*this);
      return temp;
    }

    ConstReverseIterator &operator--() {
      if (current_ != nullptr) {
        current_ = current_->next;
      }
      return *this;
    }

    ConstReverseIterator operator--(int) {
      ConstReverseIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const ConstReverseIterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ConstReverseIterator &other) const {
      return current_ != other.current_;
    }
  };

  // begin, end, cbegin, cend, rbegin, rend, crbegin, crend — возвращают
  // итераторы (изменяемые, константные и обратные)
  Iterator begin() { return Iterator(head); }
  Iterator end() { return Iterator(nullptr); }
  ConstIterator begin() const { return ConstIterator(head); }
  ConstIterator end() const { return ConstIterator(nullptr); }

  ConstIterator cbegin() const { return ConstIterator(head); }
  ConstIterator cend() const { return ConstIterator(nullptr); }

  ReverseIterator rbegin() { return ReverseIterator(tail); }
  ReverseIterator rend() { return ReverseIterator(nullptr); }

  ConstReverseIterator rbegin() const { return ConstReverseIterator(tail); }
  ConstReverseIterator rend() const { return ConstReverseIterator(nullptr); }

  ConstReverseIterator crbegin() const { return ConstReverseIterator(tail); }
  ConstReverseIterator crend() const { return ConstReverseIterator(nullptr); }

  // ---------------------------------------------------------------------
  // empty — проверяет, пуст ли список
  bool empty() const { return size_ == 0; }

  // size — возвращает количество элементов в списке
  std::size_t size() const { return size_; }

  // clear — удаляет все элементы в списке
  void clear() {
    Node *currentNode = head;
    while (currentNode != nullptr) {
      Node *nextNode = currentNode->next;
      delete currentNode;
      currentNode = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size_ = 0;
  }

  // перегрузка оператора сравнения для предотварщения самоприсваивания
  bool operator==(const LinkedList &other) const {
    if (size() != other.size()) {
      return false;
    }

    Node *currentThis = head;
    Node *currentOther = other.head;
    while (currentThis != nullptr) {
      if (currentThis->data != currentOther->data) {
        return false;
      }
      currentThis = currentThis->next;
      currentOther = currentOther->next;
    }

    return true;
  }

  bool operator!=(const LinkedList &other) const { return !(*this == other); }
};
/*Реализуйте шаблон класса «Двусвязный список» с stl-совместимыми итераторами.
Аргументируйте выбор категории итератора.

В классе должны быть реализованы следующие методы:
    Конструкторы по умолчанию.
    Конструктор от диапазона: LinkedList(It begin, It end).
    Конструктор от std::initializer_list.

    Специальные методы:
        деструктор
        копирующий конструктор
        перемещающий конструктор
        копирующий оператор присваивания
        перемещающий оператор присваивания
    front, back — возвращают ссылку на первый и последний элемент
соответственно.
    push_front, push_back — добавляют элемент в начало и в конец вектора
соответственно.
    begin, end, cbegin, cend, rbegin, rend, crbegin, crend — возвращают
итераторы (изменяемые, константные и обратные).
    empty — проверяет, пуст ли список.
    size — возвращает количество элементов в списке.
    clear — удаляет все элементы в списке.

Опционально: реализуйте deduction guides для вывода типа элемента из типа
итератора.

Проверьте работоспособность типа со следующими функциями и объясните
результаты: std::find std::reverse std::sort

Контрольные вопросы
    Что такое итератор? Как итераторы используются в стандартной библиотеке?
    Какие категории итераторов определены в стандартной библиотеке (C++17)?
*/
} // namespace linkedlist
