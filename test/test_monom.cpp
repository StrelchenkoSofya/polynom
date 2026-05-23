#include <gtest/gtest.h>
#include "monom.h"

TEST(MonomTest, Constructors) {
    Monom m1(3.5, 5);
    EXPECT_DOUBLE_EQ(m1.get_k(), 3.5);
    EXPECT_EQ(m1.get_dx(), 5);
    EXPECT_EQ(m1.get_dy(), 0);
    EXPECT_EQ(m1.get_dz(), 0);

    Monom m2(2.5, 3, 2, 1);
    EXPECT_DOUBLE_EQ(m2.get_k(), 2.5);
    EXPECT_EQ(m2.get_dx(), 3);
    EXPECT_EQ(m2.get_dy(), 2);
    EXPECT_EQ(m2.get_dz(), 1);

    Monom m3;
    EXPECT_DOUBLE_EQ(m3.get_k(), 0);
    EXPECT_EQ(m3.get_dx(), 0);
    EXPECT_EQ(m3.get_dy(), 0);
    EXPECT_EQ(m3.get_dz(), 0);
}

TEST(MonomTest, ConstructorBounds) {
    EXPECT_NO_THROW(Monom(1.0, 10, 10, 10));
    EXPECT_NO_THROW(Monom(1.0, -5, -5, -5));

    EXPECT_THROW(Monom(1.0, 11, 0, 0), int);
    EXPECT_THROW(Monom(1.0, -6, 0, 0), int);
    EXPECT_THROW(Monom(1.0, 0, 11, 0), int);
    EXPECT_THROW(Monom(1.0, 0, -6, 0), int);
    EXPECT_THROW(Monom(1.0, 0, 0, 11), int);
    EXPECT_THROW(Monom(1.0, 0, 0, -6), int);
}

TEST(MonomTest, GettersAndSetters) {
    Monom m;
    m.set_dx(3);
    m.set_dy(4);
    m.set_dz(5);
    EXPECT_EQ(m.get_dx(), 3);
    EXPECT_EQ(m.get_dy(), 4);
    EXPECT_EQ(m.get_dz(), 5);
}

TEST(MonomTest, EqualityOperators) {
    Monom m1(2.5, 3, 2, 1);
    Monom m2(2.5, 3, 2, 1);
    Monom m3(3.0, 3, 2, 1);
    Monom m4(2.5, 4, 2, 1);
    Monom m5(2.5, 3, 3, 1);
    Monom m6(2.5, 3, 2, 2);

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);

    EXPECT_TRUE(m1 == m3);
    EXPECT_FALSE(m1 != m3);

    EXPECT_FALSE(m1 == m4);
    EXPECT_TRUE(m1 != m4);

    EXPECT_FALSE(m1 == m5);
    EXPECT_TRUE(m1 != m5);

    EXPECT_FALSE(m1 == m6);
    EXPECT_TRUE(m1 != m6);
}

TEST(MonomTest, ComparisonOperators) {
    Monom m1(1.0, 2);
    Monom m2(1.0, 3);
    Monom m3(1.0, 2, 1, 0);

    EXPECT_TRUE(m1 < m2);
    EXPECT_FALSE(m2 < m1);
    EXPECT_TRUE(m2 > m1);
    EXPECT_FALSE(m1 > m2);

    EXPECT_TRUE(m1 < m3);
    EXPECT_FALSE(m3 < m1);
    EXPECT_TRUE(m3 > m1);
}

TEST(MonomTest, Addition) {
    Monom m1(2.5, 3, 2, 1);
    Monom m2(1.5, 3, 2, 1);
    Monom m3(1.0, 4, 2, 1);
    Monom result = m1 + m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 4.0);
    EXPECT_EQ(result.get_dx(), 3);
    EXPECT_EQ(result.get_dy(), 2);
    EXPECT_EQ(result.get_dz(), 1);
    EXPECT_THROW(m1 + m3, int);
}

TEST(MonomTest, Subtraction) {
    Monom m1(2.5, 3, 2, 1);
    Monom m2(1.5, 3, 2, 1);
    Monom m3(1.0, 4, 2, 1);
    Monom result = m1 - m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 1.0);
    EXPECT_EQ(result.get_dx(), 3);
    EXPECT_EQ(result.get_dy(), 2);
    EXPECT_EQ(result.get_dz(), 1);
    EXPECT_THROW(m1 - m3, int);
}

TEST(MonomTest, Multiplication) {
    Monom m1(2.0, 3, 2, 1);
    Monom m2(3.0, 1, 1, 1);
    Monom result = m1 * m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 6.0);
    EXPECT_EQ(result.get_dx(), 4);
    EXPECT_EQ(result.get_dy(), 3);
    EXPECT_EQ(result.get_dz(), 2);
}

TEST(MonomTest, MultiplicationBounds) {
    Monom m1(1.0, 10, 0, 0);
    Monom m2(1.0, 1, 0, 0);
    Monom result1 = m1 * m2;
    EXPECT_DOUBLE_EQ(result1.get_k(), 0.0);
}

TEST(MonomTest, Evaluate) {
    Monom m(2.0, 2, 1, 1);
    double result = m.init(3.0, 2.0, 4.0);
    EXPECT_DOUBLE_EQ(result, 144.0);
    Monom m2(3.0, 0, 0, 0);
    result = m2.init(5.0, 5.0, 5.0);
    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST(MonomTest, NegativeDegrees) {
    Monom m1(2.0, -2, -1, -3);
    Monom m2(3.0, -1, -2, -1);
    Monom result = m1 * m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 6.0);
    EXPECT_EQ(result.get_dx(), -3);
    EXPECT_EQ(result.get_dy(), -3);
    EXPECT_EQ(result.get_dz(), -4);

    double val = m1.init(2.0, 3.0, 4.0);
    EXPECT_NEAR(val, 0.002604166666666667, 1e-10);
}

TEST(MonomTest, Commutativity) {
    Monom m1(2.0, 3, 2, 1);
    Monom m2(3.0, 1, 2, 3);
    Monom result1 = m1 * m2;
    Monom result2 = m2 * m1;
    EXPECT_DOUBLE_EQ(result1.get_k(), result2.get_k());
    EXPECT_EQ(result1.get_dx(), result2.get_dx());
    EXPECT_EQ(result1.get_dy(), result2.get_dy());
    EXPECT_EQ(result1.get_dz(), result2.get_dz());
}

TEST(MonomTest, AdditionAssociativity) {
    Monom m1(1.0, 2, 2, 2);
    Monom m2(2.0, 2, 2, 2);
    Monom m3(3.0, 2, 2, 2);
    Monom result1 = (m1 + m2) + m3;
    Monom result2 = m1 + (m2 + m3);
    EXPECT_DOUBLE_EQ(result1.get_k(), result2.get_k());
}

TEST(MonomTest, ZeroElement) {
    Monom m1(0.0, 3, 2, 1);
    Monom m2(2.5, 3, 2, 1);
    Monom result = m1 + m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 2.5);

    result = m2 - m1;
    EXPECT_DOUBLE_EQ(result.get_k(), 2.5);

    result = m1 * m2;
    EXPECT_DOUBLE_EQ(result.get_k(), 0.0);
}

TEST(MonomTest, ExtremeValues) {
    Monom m1(1.0, 10, 10, 10);
    EXPECT_NO_THROW(m1);

    Monom m2(1.0, -5, -5, -5);
    EXPECT_NO_THROW(m2);

    Monom m3(1.0, 10, 0, 0);
    Monom m4(1.0, -5, 0, 0);
    EXPECT_THROW(m3 + m4, int);

    Monom m5(1.0, 10, 0, 0);
    Monom m6(1.0, 1, 0, 0);
    Monom result = m5 * m6;
    EXPECT_DOUBLE_EQ(result.get_k(), 0.0);
}