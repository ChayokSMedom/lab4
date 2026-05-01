#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <locale>
#include <clocale>
#include <string>
#include <iostream>

using namespace std;
// Функция для установки русской локали
void setup_russian_locale() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

// Шаблон класса Polynomial (многочлен от одной переменной)
template <typename T>
class Polynomial {
private:
    std::vector<T> coeffs;  // Коэффициенты полинома: coeffs[i] - коэффициент при x^i

    // Удаление ведущих нулевых коэффициентов
    void trim_zeros() {
        while (!coeffs.empty() && coeffs.back() == T(0)) {
            coeffs.pop_back();
        }
    }

    // Приведение размерности к одинаковой для операций
    void resize_to(size_t new_size) {
        coeffs.resize(new_size, T(0));
    }

public:
    // Конструктор по умолчанию - нулевой полином
    Polynomial() : coeffs() {}

    // Конструктор через вектор коэффициентов
    Polynomial(const std::vector<T>& coefficients) : coeffs(coefficients) {
        trim_zeros();
    }

    // Конструктор с одним коэффициентом (константный полином)
    Polynomial(const T& constant) : coeffs(1, constant) {
        if (constant == T(0)) {
            coeffs.clear();
        }
    }

    // Конструктор копирования
    Polynomial(const Polynomial& other) = default;

    // Оператор присваивания
    Polynomial& operator=(const Polynomial& other) = default;

    // Деструктор
    ~Polynomial() = default;

    // Получение степени полинома
    int degree() const {
        if (coeffs.empty()) return -1;
        return static_cast<int>(coeffs.size()) - 1;
    }

    // Получение коэффициента при степени i
    T coefficient(size_t i) const {
        if (i >= coeffs.size()) return T(0);
        return coeffs[i];
    }

    // Установка коэффициента при степени i
    void set_coefficient(size_t i, const T& value) {
        if (i >= coeffs.size()) {
            coeffs.resize(i + 1, T(0));
        }
        coeffs[i] = value;
        trim_zeros();
    }

    // Вычисление значения полинома в точке x
    T evaluate(const T& x) const {
        if (coeffs.empty()) return T(0);

        T result = T(0);
        T power = T(1);

        for (size_t i = 0; i < coeffs.size(); ++i) {
            result = result + coeffs[i] * power;
            power = power * x;
        }

        return result;
    }

    // Оператор сложения с присваиванием
    Polynomial& operator+=(const Polynomial& other) {
        size_t max_size = std::max(coeffs.size(), other.coeffs.size());
        resize_to(max_size);

        for (size_t i = 0; i < other.coeffs.size(); ++i) {
            coeffs[i] = coeffs[i] + other.coeffs[i];
        }

        trim_zeros();
        return *this;
    }

    // Оператор вычитания с присваиванием
    Polynomial& operator-=(const Polynomial& other) {
        size_t max_size = std::max(coeffs.size(), other.coeffs.size());
        resize_to(max_size);

        for (size_t i = 0; i < other.coeffs.size(); ++i) {
            coeffs[i] = coeffs[i] - other.coeffs[i];
        }

        trim_zeros();
        return *this;
    }

    // Оператор умножения с присваиванием
    Polynomial& operator*=(const Polynomial& other) {
        if (coeffs.empty() || other.coeffs.empty()) {
            coeffs.clear();
            return *this;
        }

        std::vector<T> new_coeffs(coeffs.size() + other.coeffs.size() - 1, T(0));

        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); ++j) {
                new_coeffs[i + j] = new_coeffs[i + j] + coeffs[i] * other.coeffs[j];
            }
        }

        coeffs = std::move(new_coeffs);
        trim_zeros();
        return *this;
    }

    // Оператор умножения на константу
    Polynomial& operator*=(const T& scalar) {
        if (scalar == T(0)) {
            coeffs.clear();
        } else {
            for (size_t i = 0; i < coeffs.size(); ++i) {
                coeffs[i] = coeffs[i] * scalar;
            }
        }
        return *this;
    }

    // Оператор деления с присваиванием
    Polynomial& operator/=(const Polynomial& divisor) {
        *this = *this / divisor;
        return *this;
    }

    // Оператор остатка от деления с присваиванием
    Polynomial& operator%=(const Polynomial& divisor) {
        *this = *this % divisor;
        return *this;
    }

    // Проверка на равенство
    bool operator==(const Polynomial& other) const {
        if (coeffs.size() != other.coeffs.size()) return false;
        for (size_t i = 0; i < coeffs.size(); ++i) {
            if (coeffs[i] != other.coeffs[i]) return false;
        }
        return true;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    // Получение вектора коэффициентов
    const std::vector<T>& get_coefficients() const {
        return coeffs;
    }

    // Проверка на нулевой полином
    bool is_zero() const {
        return coeffs.empty();
    }
};

// ==================== Бинарные операторы ====================

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial<T> result(lhs);
    result += rhs;
    return result;
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial<T> result(lhs);
    result -= rhs;
    return result;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    Polynomial<T> result(lhs);
    result *= rhs;
    return result;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& poly, const T& scalar) {
    Polynomial<T> result(poly);
    result *= scalar;
    return result;
}

template <typename T>
Polynomial<T> operator*(const T& scalar, const Polynomial<T>& poly) {
    return poly * scalar;
}

template <typename T>
Polynomial<T> operator/(const Polynomial<T>& dividend, const Polynomial<T>& divisor) {
    if (divisor.is_zero()) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    if (dividend.degree() < divisor.degree()) {
        return Polynomial<T>();
    }

    Polynomial<T> remainder(dividend);
    Polynomial<T> quotient;

    while (!remainder.is_zero() && remainder.degree() >= divisor.degree()) {
        int deg_diff = remainder.degree() - divisor.degree();
        T leading_coeff = remainder.coefficient(remainder.degree()) / divisor.coefficient(divisor.degree());

        std::vector<T> term_coeffs(deg_diff + 1, T(0));
        term_coeffs[deg_diff] = leading_coeff;
        Polynomial<T> term(term_coeffs);

        quotient += term;
        remainder -= term * divisor;
    }

    return quotient;
}

template <typename T>
Polynomial<T> operator%(const Polynomial<T>& dividend, const Polynomial<T>& divisor) {
    if (divisor.is_zero()) {
        throw std::invalid_argument("Modulo by zero polynomial");
    }

    Polynomial<T> remainder(dividend);

    while (!remainder.is_zero() && remainder.degree() >= divisor.degree()) {
        int deg_diff = remainder.degree() - divisor.degree();
        T leading_coeff = remainder.coefficient(remainder.degree()) / divisor.coefficient(divisor.degree());

        std::vector<T> term_coeffs(deg_diff + 1, T(0));
        term_coeffs[deg_diff] = leading_coeff;
        Polynomial<T> term(term_coeffs);

        remainder -= term * divisor;
    }

    return remainder;
}

#endif // POLYNOMIAL_HPP
