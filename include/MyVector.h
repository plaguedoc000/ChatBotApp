#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class MyVector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    MyVector();
    explicit MyVector(size_type count, const T& value = T());
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector(std::initializer_list<T> init);
    ~MyVector();

    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    MyVector& operator=(std::initializer_list<T> ilist);

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data() noexcept;
    const T* data() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);
    void shrink_to_fit();

    void clear() noexcept;
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void swap(MyVector& other) noexcept;

private:
    T* m_data;
    size_type m_size;
    size_type m_capacity;

    void reallocate(size_type new_capacity);
};

template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator<(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator<=(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator>(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator>=(const MyVector<T>& lhs, const MyVector<T>& rhs);

// Включаем реализацию
#include "MyVector.inl"

#endif // MYVECTOR_H
