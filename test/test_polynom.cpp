#include <gtest/gtest.h>
#include "polynom.h"
#include "monom.h"
#include<string>
#include<sstream>

TEST(PolynomTest, ConstructorAndBasic) {
    Polynom p;
    EXPECT_TRUE(p.retMonom().isEmpty());
}

TEST(PolynomTest, AddMonom) {
    Polynom p;
    Monom m1(2.5, 3, 2, 1);
    p.add(m1);
    EXPECT_FALSE(p.retMonom().isEmpty());
}

TEST(PolynomTest, AdditionSameDegrees) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 3, 2, 1));
    p1.add(Monom(1.0, 2, 1, 0));
    p2.add(Monom(3.0, 3, 2, 1));
    p2.add(Monom(2.0, 2, 1, 0));
    Polynom p = p1 + p2;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 5.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 3);
    EXPECT_EQ(p.getMonom(1).get_dy(), 2);
    EXPECT_EQ(p.getMonom(1).get_dz(), 1);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 3.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 2);
    EXPECT_EQ(p.getMonom(0).get_dy(), 1);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, AdditionDifferentDegrees) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 3, 0, 0));
    p2.add(Monom(4.0, 0, 0, 1));
    Polynom p = p1 + p2;
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 3);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 4.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 0);
    EXPECT_EQ(p.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p.getMonom(1).get_dz(), 1);
}

TEST(PolynomTest, Subtraction) {
    Polynom p1, p2;
    p1.add(Monom(5.0, 3, 2, 1));
    p1.add(Monom(3.0, 2, 1, 0));
    p2.add(Monom(2.0, 3, 2, 1));
    p2.add(Monom(1.0, 2, 1, 0));
    Polynom p = p1 - p2;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 3.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 3);
    EXPECT_EQ(p.getMonom(1).get_dy(), 2);
    EXPECT_EQ(p.getMonom(1).get_dz(), 1);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 2);
    EXPECT_EQ(p.getMonom(0).get_dy(), 1);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, Multiplication) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 1, 0, 0));
    p1.add(Monom(1.0, 0, 0, 0));
    p2.add(Monom(2.0, 0, 0, 0));
    Polynom p = p1 * p2;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 4.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 1);
    EXPECT_EQ(p.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 0);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, Evaluate) {
    Polynom p;
    p.add(Monom(2.0, 2, 0, 0));
    p.add(Monom(3.0, 1, 0, 0));
    p.add(Monom(1.0, 0, 0, 0));
    double result = p.init(2.0, 0, 0);
    EXPECT_DOUBLE_EQ(result, 15.0);
}

TEST(PolynomTest, EvaluateThreeVariables) {
    Polynom p;
    p.add(Monom(2.0, 2, 1, 1));
    p.add(Monom(3.0, 1, 2, 0));
    p.add(Monom(1.0, 0, 0, 0));
    double result = p.init(2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(result, 151.0);
}

TEST(PolynomTest, AdditionWithZeroCoefficients) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 3, 2, 1));
    p1.add(Monom(0.0, 2, 1, 0));
    p2.add(Monom(3.0, 3, 2, 1));
    Polynom result = p1 + p2;
    std::stringstream ss;
    ss << result;
    EXPECT_FALSE(ss.str().empty());
}

TEST(PolynomTest, MultiplyByEmpty) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 1, 0, 0));
    Polynom result = p1 * p2;
    std::stringstream ss;
    ss << result;
    EXPECT_TRUE(ss.str().empty() || result.ret_list().isEmpty());
}

TEST(PolynomTest, AddEmptyPolynom) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 1, 0, 0));
    p1.add(Monom(1.0, 0, 0, 0));

    Polynom result = p1 + p2;

    std::stringstream ss1, ss2;
    ss1 << p1;
    ss2 << result;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(PolynomTest, SubtractItself) {
    Polynom p;
    p.add(Monom(2.0, 1, 0, 0));
    p.add(Monom(3.0, 0, 1, 0));
    p.add(Monom(1.0, 0, 0, 0));
    Polynom result = p - p;
    std::stringstream ss;
    ss << result;
    EXPECT_TRUE(ss.str().empty() || result.ret_list().isEmpty());
}

TEST(PolynomTest, AdditionAssociativity) {
    Polynom p1, p2, p3;
    p1.add(Monom(1.0, 2, 0, 0));
    p2.add(Monom(2.0, 1, 0, 0));
    p3.add(Monom(3.0, 0, 0, 0));
    Polynom result1 = (p1 + p2) + p3;
    Polynom result2 = p1 + (p2 + p3);
    std::stringstream ss1, ss2;
    ss1 << result1;
    ss2 << result2;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(PolynomTest, AdditionCommutativity) {
    Polynom p1, p2;
    p1.add(Monom(1.0, 2, 0, 0));
    p1.add(Monom(2.0, 1, 0, 0));
    p2.add(Monom(3.0, 1, 0, 0));
    p2.add(Monom(4.0, 0, 0, 0));
    Polynom result1 = p1 + p2;
    Polynom result2 = p2 + p1;
    std::stringstream ss1, ss2;
    ss1 << result1;
    ss2 << result2;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(PolynomTest, SameDegrees) {
    Polynom p;
    p.add(Monom(2.0, 2, 1, 0));
    p.add(Monom(3.0, 2, 1, 0));
    p.add(Monom(1.0, 2, 1, 0));
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 6.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 2);
    EXPECT_EQ(p.getMonom(0).get_dy(), 1);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, NegativeDegrees) {
    Polynom p;
    p.add(Monom(2.0, -1, 0, 0));
    p.add(Monom(3.0, -2, 0, 0));
    double result = p.init(2.0, 0, 0);
    EXPECT_DOUBLE_EQ(result, 1.75);
}

TEST(PolynomTest, CopyPolynom) {
    Polynom p1;
    p1.add(Monom(2.0, 1, 0, 0));
    p1.add(Monom(1.0, 0, 0, 0));
    Polynom p = p1;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 1);
    EXPECT_EQ(p.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 1.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 0);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
    p1.add(Monom(3.0, 2, 0, 0));
    EXPECT_DOUBLE_EQ(p1.getMonom(2).get_k(), 3.0);
    EXPECT_EQ(p1.getMonom(2).get_dx(), 2);
    EXPECT_EQ(p1.getMonom(2).get_dy(), 0);
    EXPECT_EQ(p1.getMonom(2).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p1.getMonom(1).get_k(), 2.0);
    EXPECT_EQ(p1.getMonom(1).get_dx(), 1);
    EXPECT_EQ(p1.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p1.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p1.getMonom(0).get_k(), 1.0);
    EXPECT_EQ(p1.getMonom(0).get_dx(), 0);
    EXPECT_EQ(p1.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p1.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, AssignmentOperator) {
    Polynom p1;
    p1.add(Monom(2.0, 1, 0, 0));
    p1.add(Monom(1.0, 0, 0, 0));
    Polynom p;
    p = p1;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 1);
    EXPECT_EQ(p.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 1.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 0);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, EmptyPolynom) {
    Polynom p;
    EXPECT_TRUE(p.retMonom().isEmpty());
    double result = p.init(1.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(PolynomTest, AdditionWithReduction) {
    Polynom p1, p2;
    p1.add(Monom(2.0, 2, 1, 0));
    p1.add(Monom(1.0, 1, 0, 0));
    p2.add(Monom(3.0, 2, 1, 0));
    p2.add(Monom(2.0, 1, 0, 0));
    Polynom p = p1 + p2;
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 5.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 2);
    EXPECT_EQ(p.getMonom(1).get_dy(), 1);
    EXPECT_EQ(p.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 3.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 1);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}

TEST(PolynomTest, AntlrParse) {
    Polynom p("2.0x^3+1.0");
    EXPECT_DOUBLE_EQ(p.getMonom(1).get_k(), 2.0);
    EXPECT_EQ(p.getMonom(1).get_dx(), 3);
    EXPECT_EQ(p.getMonom(1).get_dy(), 0);
    EXPECT_EQ(p.getMonom(1).get_dz(), 0);
    EXPECT_DOUBLE_EQ(p.getMonom(0).get_k(), 1.0);
    EXPECT_EQ(p.getMonom(0).get_dx(), 0);
    EXPECT_EQ(p.getMonom(0).get_dy(), 0);
    EXPECT_EQ(p.getMonom(0).get_dz(), 0);
}