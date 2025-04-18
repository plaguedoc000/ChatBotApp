#include "MyVector.h"

// Конструкторы и деструктор
template <typename T>
MyVector<T>::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
MyVector<T>::MyVector(size_type count, const T& value) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (count > 0) {
        m_data = new T[count];
        m_size = count;
        m_capacity = count;
        for (size_type i = 0; i < count; ++i) {
            m_data[i] = value;
        }
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (other.m_size > 0) {
        m_data = new T[other.m_size];
        m_size = other.m_size;
        m_capacity = other.m_size;
        for (size_type i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> init) : m_data(nullptr), m_size(0), m_capacity(0) {
    size_type count = init.size();
    if (count > 0) {
        m_data = new T[count];
        m_size = count;
        m_capacity = count;
        size_type i = 0;
        for (const auto& item : init) {
            m_data[i++] = item;
        }
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] m_data;
}

// Операторы присваивания
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        MyVector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(std::initializer_list<T> ilist) {
    MyVector temp(ilist);
    swap(temp);
    return *this;
}

// Доступ к элементам
template <typename T>
typename MyVector<T>::reference MyVector<T>::at(size_type pos) {
    if (pos >= m_size) {
        throw std::out_of_range("MyVector::at: pos out of range");
    }
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::at(size_type pos) const {
    if (pos >= m_size) {
        throw std::out_of_range("MyVector::at: pos out of range");
    }
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::operator[](size_type pos) {
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::operator[](size_type pos) const {
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::front() {
    return m_data[0];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::front() const {
    return m_data[0];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::back() {
    return m_data[m_size - 1];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::back() const {
    return m_data[m_size - 1];
}

template <typename T>
T* MyVector<T>::data() noexcept {
    return m_data;
}

template <typename T>
const T* MyVector<T>::data() const noexcept {
    return m_data;
}

// Итераторы
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() noexcept {
    return m_data;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const noexcept {
    return m_data;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::cbegin() const noexcept {
    return m_data;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() noexcept {
    return m_data + m_size;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const noexcept {
    return m_data + m_size;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::cend() const noexcept {
    return m_data + m_size;
}

// Емкость
template <typename T>
bool MyVector<T>::empty() const noexcept {
    return m_size == 0;
}

template <typename T>
typename MyVector<T>::size_type MyVector<T>::size() const noexcept {
    return m_size;
}

template <typename T>
typename MyVector<T>::size_type MyVector<T>::capacity() const noexcept {
    return m_capacity;
}

template <typename T>
void MyVector<T>::reserve(size_type new_cap) {
    if (new_cap > m_capacity) {
        reallocate(new_cap);
    }
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
    if (m_size < m_capacity) {
        reallocate(m_size);
    }
}

// Модификаторы
template <typename T>
void MyVector<T>::clear() noexcept {
    m_size = 0;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, const T& value) {
    size_type position = pos - m_data;
    if (m_size == m_capacity) {
        size_type new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
        reallocate(new_capacity);
    }
    
    // Сдвигаем элементы
    for (size_type i = m_size; i > position; --i) {
        m_data[i] = std::move(m_data[i - 1]);
    }

    m_data[position] = value;
    ++m_size;
    return m_data + position;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, T&& value) {
    size_type position = pos - m_data;
    if (m_size == m_capacity) {
        size_type new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
        reallocate(new_capacity);
    }
    
    // Сдвигаем элементы
    for (size_type i = m_size; i > position; --i) {
        m_data[i] = std::move(m_data[i - 1]);
    }

    m_data[position] = std::move(value);
    ++m_size;
    return m_data + position;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, size_type count, const T& value) {
    if (count == 0) {
        return const_cast<iterator>(pos);
    }

    size_type position = pos - m_data;
    size_type new_size = m_size + count;
    
    if (new_size > m_capacity) {
        size_type new_capacity = new_size > m_capacity * 2 ? new_size : m_capacity * 2;
        reallocate(new_capacity);
    }
    
    // Сдвигаем элементы
    for (size_type i = m_size + count - 1; i >= position + count; --i) {
        m_data[i] = std::move(m_data[i - count]);
    }

    // Вставляем новые элементы
    for (size_type i = 0; i < count; ++i) {
        m_data[position + i] = value;
    }
    
    m_size = new_size;
    return m_data + position;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator pos) {
    size_type position = pos - m_data;
    
    for (size_type i = position; i < m_size - 1; ++i) {
        m_data[i] = std::move(m_data[i + 1]);
    }
    
    --m_size;
    return m_data + position;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator first, const_iterator last) {
    size_type start = first - m_data;
    size_type count = last - first;
    
    if (count == 0) {
        return m_data + start;
    }
    
    for (size_type i = start; i <= m_size - count - 1; ++i) {
        m_data[i] = std::move(m_data[i + count]);
    }
    
    m_size -= count;
    return m_data + start;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        size_type new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
        reallocate(new_capacity);
    }
    
    m_data[m_size] = value;
    ++m_size;
}

template <typename T>
void MyVector<T>::push_back(T&& value) {
    if (m_size == m_capacity) {
        size_type new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
        reallocate(new_capacity);
    }
    
    m_data[m_size] = std::move(value);
    ++m_size;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (m_size > 0) {
        --m_size;
    }
}

template <typename T>
void MyVector<T>::resize(size_type count) {
    resize(count, T());
}

template <typename T>
void MyVector<T>::resize(size_type count, const value_type& value) {
    if (count > m_size) {
        // Увеличиваем размер
        if (count > m_capacity) {
            reallocate(count);
        }
        for (size_type i = m_size; i < count; ++i) {
            m_data[i] = value;
        }
    }
    m_size = count;
}

template <typename T>
void MyVector<T>::swap(MyVector& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
}

// Вспомогательные функции
template <typename T>
void MyVector<T>::reallocate(size_type new_capacity) {
    T* new_data = new T[new_capacity];
    
    size_type copy_size = m_size < new_capacity ? m_size : new_capacity;
    for (size_type i = 0; i < copy_size; ++i) {
        new_data[i] = std::move(m_data[i]);
    }
    
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_capacity;
}

// Нерелевантные операторы
template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    
    for (typename MyVector<T>::size_type i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    
    return true;
}

template <typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return !(rhs < lhs);
}

template <typename T>
bool operator>(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator>=(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return !(lhs < rhs);
}