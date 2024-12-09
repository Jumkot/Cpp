#include "String.hpp"

// Конструктор по умолчанию
String::String() : data_(new char[1]), size_(0)
{
    data_[0] = '\0';
}

// Конструктор с параметром
String::String(const char* str)
{
    size_ = 0;
    while (str[size_] != '\0') {
        ++size_; // Считаем длину строки
    }
    data_ = new char[size_ + 1]; // Выделяем память под строку + '\0'
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = str[i]; // Копируем символы
    }
    data_[size_] = '\0'; // Завершаем строку
}

// Копирующий конструктор
String::String(const String& other)
    : data_(new char[other.size_ + 1]), size_(other.size_)
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i]; // Копируем символы
    }
    data_[size_] = '\0'; // Завершаем строку
}

// Перемещающий конструктор
String::String(String&& other) noexcept : data_(other.data_), size_(other.size_)
{
    other.data_ = new char[1]; // Переводим в пустое состояние
    other.data_[0] = '\0';
    other.size_ = 0;
}

// Копирующее присваивание
String& String::operator=(const String& other)
{
    if (this != &other) { // Проверяем самоприсваивание
        delete[] data_;   // Удаляем старую строку
        size_ = other.size_;
        data_ = new char[size_ + 1]; // Выделяем новую память
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i]; // Копируем символы
        }
        data_[size_] = '\0'; // Завершаем строку
    }
    return *this; // Возвращаем текущий объект
}

// Перемещающее присваивание
String& String::operator=(String&& other) noexcept
{
    if (this != &other) {
        delete[] data_;      // Удаляем старые данные
        data_ = other.data_; // Перемещаем указатель
        size_ = other.size_;
        other.data_ = new char[1]; // Переводим в пустое состояние
        other.data_[0] = '\0';
        other.size_ = 0;
    }
    return *this;
}
// Деструктор
String::~String()
{
    delete[] data_;
}

// Возвращает null-терминированную строку
const char* String::c_str() const noexcept
{
    return data_;
}

// Возвращает длину строки
std::size_t String::size() const noexcept
{
    return size_;
}

// Доступ к символу по индексу с проверкой
char& String::at(std::size_t idx)
{
    if (idx >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[idx];
}

const char& String::at(std::size_t idx) const
{
    if (idx >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[idx];
}
