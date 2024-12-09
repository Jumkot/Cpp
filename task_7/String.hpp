#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>   // Для std::size_t
#include <stdexcept> // Для std::out_of_range

class String {
private:
    char* data_;       // Строка
    std::size_t size_; // Длина строки без /0

public:
    // Конструктор по умолчанию
    String();

    // Конструктор с параметром
    explicit String(const char* str);

    // Копирующий конструктор
    String(const String& other);

    // Перемещающий конструктор
    String(String&& other) noexcept;

    // Копирующее присваивание
    String& operator=(const String& other);

    // Перемещающее присваивание
    String& operator=(String&& other) noexcept;

    // Деструктор
    ~String();

    // Возвращает null-терминированную строку
    const char* c_str() const noexcept;

    // Возвращает длину строки
    std::size_t size() const noexcept;

    // Доступ к символу по индексу с проверкой
    char& at(std::size_t idx);
    const char& at(std::size_t idx) const;
};

#endif