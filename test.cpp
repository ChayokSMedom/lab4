#include <iostream>
#include "polynomial.cpp"

using namespace std;

int main() {
    setup_russian_locale();

    cout << "=== Демонстрация работы класса Polynomial ===" << endl;

    // Создание полиномов
    Polynomial<int> p1({1, 2, 3});  // 1 + 2x + 3x^2
    Polynomial<int> p2({4, 5});      // 4 + 5x

    cout << "p1 = 1 + 2x + 3x^2" << endl;
    cout << "p2 = 4 + 5x" << endl;

    // Сложение
    Polynomial<int> sum = p1 + p2;
    cout << "p1 + p2 = " << sum.coefficient(0) << " + "
         << sum.coefficient(1) << "x + " << sum.coefficient(2) << "x^2" << endl;

    // Вычитание
    Polynomial<int> diff = p1 - p2;
    cout << "p1 - p2 = " << diff.coefficient(0) << " + "
         << diff.coefficient(1) << "x + " << diff.coefficient(2) << "x^2" << endl;

    // Умножение
    Polynomial<int> prod = p1 * p2;
    cout << "p1 * p2 = " << prod.coefficient(0) << " + "
         << prod.coefficient(1) << "x + " << prod.coefficient(2) << "x^2 + "
         << prod.coefficient(3) << "x^3" << endl;

    // Деление
    Polynomial<int> p3({1, 0, 0, 1});  // 1 + x^3
    Polynomial<int> p4({1, 1});         // 1 + x
    Polynomial<int> quotient = p3 / p4;
    cout << "\n(1 + x^3) / (1 + x) = " << quotient.coefficient(0) << " + "
         << quotient.coefficient(1) << "x + " << quotient.coefficient(2) << "x^2" << endl;

    // Вычисление значения
    cout << "\np1(2) = " << p1.evaluate(2) << endl;
    cout << "p2(3) = " << p2.evaluate(3) << endl;

    // Степень полинома
    cout << "\nСтепень p1: " << p1.degree() << endl;
    cout << "Степень нулевого полинома: " << Polynomial<int>().degree() << endl;

    return 0;
}
