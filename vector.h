#ifndef NEURAL_NETWORKS_VECTOR_H
#define NEURAL_NETWORKS_VECTOR_H

#include <iostream>

template <typename T>
class Vector {
public:

    Vector(): capacity_(1), size_(0) {
        data_ = new T[capacity_];
    }

    Vector(size_t size):capacity_(1), size_(0) {
        data_ = new T[capacity_];
        while (capacity_ < size) {
            resize();
        }
        size_ = size;
    }

    // конструктор копирования
    Vector(const Vector& other): capacity_(other.capacity_), size_(other.size_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // конструктор перемещения
    Vector(Vector&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Оператор присваивания копированием
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;

            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void PushBack(const T& value) {
        if (size_ == capacity_) {
            resize();
        }
        data_[size_] = value;
        size_++;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::out_of_range("No elements to pop");
        }
        size_--;
    }

    void Clear() {
        size_ = 0;
    }

    void Resize(const size_t new_size) {
        if (new_size > capacity_) {
            while (capacity_ < new_size) {
                resize();
            }
        }

        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = T();
            }
        }
        size_ = new_size;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    T& Back() {
        if (size_ > 0) {
            return data_[size_ - 1];
        }
        throw std::out_of_range("Vector is empty");
    }

    T& Front() {
        if (size_ > 0) {
            return data_[0];
        }
        throw std::out_of_range("Vector is empty");
    }

private:
    T* data_;
    size_t capacity_;
    size_t size_;

    void resize() {
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
};

#endif //NEURAL_NETWORKS_VECTOR_H
