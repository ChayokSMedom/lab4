#include <gtest/gtest.h>
#include "polynomial.cpp"

// Точка входа для Google Test
int main(int argc, char** argv) {
    setup_russian_locale();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ==================== Тесты для конструкторов ====================

TEST(PolynomialTest, DefaultConstructor) {
    Polynomial<int> p;
    EXPECT_EQ(p.degree(), -1);
    EXPECT_TRUE(p.is_zero());
    EXPECT_EQ(p.get_coefficients().size(), 0u);
}

TEST(PolynomialTest, VectorConstructor) {
    std::vector<int> coeffs = {1, 2, 3};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p.coefficient(0), 1);
    EXPECT_EQ(p.coefficient(1), 2);
    EXPECT_EQ(p.coefficient(2), 3);
}

TEST(PolynomialTest, ConstantConstructor) {
    Polynomial<int> p(5);
    EXPECT_EQ(p.degree(), 0);
    EXPECT_EQ(p.coefficient(0), 5);

    Polynomial<int> p_zero(0);
    EXPECT_TRUE(p_zero.is_zero());
}

TEST(PolynomialTest, ZeroVectorConstructor) {
    std::vector<int> coeffs = {0, 0, 0};
    Polynomial<int> p(coeffs);
    EXPECT_TRUE(p.is_zero());
    EXPECT_EQ(p.degree(), -1);
}

// ==================== Тесты для degree и coefficient ====================

TEST(PolynomialTest, DegreeTest) {
    EXPECT_EQ(Polynomial<int>({1, 2, 3}).degree(), 2);
    EXPECT_EQ(Polynomial<int>({0, 0, 5}).degree(), 2);
    EXPECT_EQ(Polynomial<int>({0, 0, 0}).degree(), -1);
    EXPECT_EQ(Polynomial<int>({5}).degree(), 0);
}

TEST(PolynomialTest, CoefficientTest) {
    Polynomial<int> p({1, 2, 3, 4});
    EXPECT_EQ(p.coefficient(0), 1);
    EXPECT_EQ(p.coefficient(1), 2);
    EXPECT_EQ(p.coefficient(2), 3);
    EXPECT_EQ(p.coefficient(3), 4);
    EXPECT_EQ(p.coefficient(10), 0);
}

TEST(PolynomialTest, SetCoefficientTest) {
    Polynomial<int> p({1, 1, 1});
    p.set_coefficient(1, 5);
    EXPECT_EQ(p.coefficient(1), 5);

    p.set_coefficient(5, 10);
    EXPECT_EQ(p.coefficient(5), 10);
    EXPECT_EQ(p.degree(), 5);
}

// ==================== Тесты для сложения ====================

TEST(PolynomialTest, AdditionTest) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({4, 5});
    Polynomial<int> result = p1 + p2;

    EXPECT_EQ(result.coefficient(0), 5);
    EXPECT_EQ(result.coefficient(1), 7);
    EXPECT_EQ(result.coefficient(2), 3);
}

TEST(PolynomialTest, AdditionAssignTest) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({4, 5});
    p1 += p2;

    EXPECT_EQ(p1.coefficient(0), 5);
    EXPECT_EQ(p1.coefficient(1), 7);
    EXPECT_EQ(p1.coefficient(2), 3);
}

// ==================== Тесты для вычитания ====================

TEST(PolynomialTest, SubtractionTest) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({4, 5});
    Polynomial<int> result = p1 - p2;

    EXPECT_EQ(result.coefficient(0), -3);
    EXPECT_EQ(result.coefficient(1), -3);
    EXPECT_EQ(result.coefficient(2), 3);
}

TEST(PolynomialTest, SubtractionResultZero) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({1, 2, 3});
    Polynomial<int> result = p1 - p2;

    EXPECT_TRUE(result.is_zero());
}

// ==================== Тесты для умножения ====================

TEST(PolynomialTest, MultiplicationTest) {
    Polynomial<int> p1({1, 1});
    Polynomial<int> p2({1, -1});
    Polynomial<int> result = p1 * p2;

    EXPECT_EQ(result.coefficient(0), 1);
    EXPECT_EQ(result.coefficient(1), 0);
    EXPECT_EQ(result.coefficient(2), -1);
}

TEST(PolynomialTest, MultiplicationWithConstant) {
    Polynomial<int> p({1, 2, 3});
    Polynomial<int> result = p * 2;

    EXPECT_EQ(result.coefficient(0), 2);
    EXPECT_EQ(result.coefficient(1), 4);
    EXPECT_EQ(result.coefficient(2), 6);
}

TEST(PolynomialTest, MultiplicationByZero) {
    Polynomial<int> p({1, 2, 3});
    Polynomial<int> result = p * 0;
    EXPECT_TRUE(result.is_zero());
}

// ==================== Тесты для деления ====================

TEST(PolynomialTest, DivisionTest) {
    Polynomial<int> p1({1, 0, 0, 1});
    Polynomial<int> p2({1, 1});
    Polynomial<int> quotient = p1 / p2;

    EXPECT_EQ(quotient.coefficient(0), 1);
    EXPECT_EQ(quotient.coefficient(1), -1);
    EXPECT_EQ(quotient.coefficient(2), 1);
}

TEST(PolynomialTest, DivisionWithRemainder) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({1, 1});
    Polynomial<int> remainder = p1 % p2;

    EXPECT_EQ(remainder.coefficient(0), 2);
    EXPECT_EQ(remainder.degree(), 0);
}

TEST(PolynomialTest, DivisionByZeroThrows) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2;

    EXPECT_THROW(p1 / p2, std::invalid_argument);
    EXPECT_THROW(p1 % p2, std::invalid_argument);
}

// ==================== Тесты для evaluate ====================

TEST(PolynomialTest, EvaluateTest) {
    Polynomial<int> p({1, 2, 3});

    EXPECT_EQ(p.evaluate(0), 1);
    EXPECT_EQ(p.evaluate(1), 6);
    EXPECT_EQ(p.evaluate(2), 17);
    EXPECT_EQ(p.evaluate(-1), 2);
}

TEST(PolynomialTest, EvaluateZeroPolynomial) {
    Polynomial<int> p;
    EXPECT_EQ(p.evaluate(100), 0);
}

// ==================== Тесты для сравнения ====================

TEST(PolynomialTest, EqualityTest) {
    Polynomial<int> p1({1, 2, 3});
    Polynomial<int> p2({1, 2, 3});
    Polynomial<int> p3({1, 2});

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(PolynomialTest, EqualityWithZeros) {
    Polynomial<int> p1({1, 0, 0});
    Polynomial<int> p2({1});

    EXPECT_TRUE(p1 == p2);
}

// ==================== Тесты для вещественных чисел ====================

TEST(PolynomialTest, DoubleCoefficients) {
    Polynomial<double> p({1.5, 2.5, 3.5});

    EXPECT_DOUBLE_EQ(p.coefficient(0), 1.5);
    EXPECT_DOUBLE_EQ(p.coefficient(1), 2.5);
    EXPECT_DOUBLE_EQ(p.coefficient(2), 3.5);
}
