#include <gtest/gtest.h>
#include "../include/lab.h"
#include <sstream>
#include <iostream>

// Тесты конструкторов

TEST(CtorsDtorsSet, DefaultConstructor) {
    Money money;
    EXPECT_EQ(money.GetSize(), 1);
    EXPECT_NE(money.GetDigits(), nullptr);
}

TEST(CtorsDtorsSet, StringConstructor) {
    Money money("123.45");
    EXPECT_EQ(money.GetSize(), 5); // Проверяем размер
    EXPECT_EQ(money.GetDigits()[0], 5); // Копейки
    EXPECT_EQ(money.GetDigits()[1], 4); // Копейки
    EXPECT_EQ(money.GetDigits()[2], 3); // Рубли
    EXPECT_EQ(money.GetDigits()[3], 2); // Рубли
    EXPECT_EQ(money.GetDigits()[4], 1); // Рубли
}

TEST(CtorsDtorsSet, DoubleConstructor) {
    Money money(123.45);
    EXPECT_EQ(money.GetSize(), 5); // Проверяем размер
    EXPECT_EQ(money.GetDigits()[0], 5); // Копейки
    EXPECT_EQ(money.GetDigits()[1], 4); // Копейки
    EXPECT_EQ(money.GetDigits()[2], 3); // Рубли
    EXPECT_EQ(money.GetDigits()[3], 2); // Рубли
    EXPECT_EQ(money.GetDigits()[4], 1); // Рубли
}

TEST(CtorsDtorsSet, InvalidString) {
    EXPECT_THROW(Money money("123.4a5"), std::invalid_argument);
}

// Тесты преобразования в строку и вывод

TEST(ToStringSet, PrintOperator) {
    std::ostringstream oss;
    Money money(123.45);
    oss << money;
    EXPECT_EQ(oss.str(), "123.45");

    std::ostringstream oss2;
    Money money2{};
    oss2 << money2;
    EXPECT_EQ(oss2.str(), "0.00");
}

TEST(ToStringSet, ToStringMethod) {
    Money money(123.45);
    EXPECT_EQ(money.ToString(), "123.45");
    EXPECT_EQ(money.ToString('$'), "123$45");

    Money money2{};
    EXPECT_EQ(money2.ToString(), "0.00");
    EXPECT_EQ(money2.ToString('#'), "0#00");
}

// Тесты операций отношения и равенства

TEST(LogicalSet, EqOp) {
    Money m1(123.45);
    Money m2("0123.45");
    EXPECT_TRUE(m1 == m2);

    Money m3{};
    Money m4(0);
    EXPECT_TRUE(m3 == m4);

    EXPECT_FALSE(m1 == m3);
}

TEST(LogicalSet, NeqOp) {
    Money m1(123.45);
    Money m2(123.44);
    Money m3("000123.44");

    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m2 != m3);
}

TEST(LogicalSet, LtOp) {
    Money m1(123.45);
    Money m2(12.34);

    EXPECT_FALSE(m1 < m2);
    EXPECT_TRUE(m2 < m1);
}

TEST(LogicalSet, GtOp) {
    Money m1(123.45);
    Money m2(12.34);

    EXPECT_TRUE(m1 > m2);
    EXPECT_FALSE(m2 > m1);
}

TEST(LogicalSet, LeqOp) {
    Money m1(123.45);
    Money m2(12.34);
    Money m3("123.45");


    EXPECT_FALSE(m1 <= m2);
    EXPECT_TRUE(m2 <= m1);
    EXPECT_TRUE(m1 <= m3);
}

TEST(LogicalSet, GeqOp) {
    Money m1(123.45);
    Money m2(12.34);
    Money m3("123.45");

    EXPECT_TRUE(m1 >= m2);
    EXPECT_FALSE(m2 >= m1);
    EXPECT_TRUE(m1 >= m3);
}

// Тесты арифметических операций

TEST(ArithmeticSet, SumEqOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    m1 += m2;
    EXPECT_EQ(m1, Money(15.12));
    
    m1 += Money();
    EXPECT_EQ(m1, Money(15.12));

    Money m3(99.99);
    Money m4(99.91);
    m3 += m4;
    EXPECT_EQ(m3, Money(199.9));
}

TEST(ArithmeticSet, SubEqOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    m1 -= m2;
    EXPECT_EQ(m1, Money(5.34));
    
    m1 -= Money();
    EXPECT_EQ(m1, Money(5.34));

    Money m3(99.99);
    Money m4(99.91);
    m3 -= m4;
    EXPECT_EQ(m3, Money(0.08));

    EXPECT_THROW(m3 -= m4, std::invalid_argument);
}

TEST(ArithmeticSet, MulEqOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    m1 *= m2;
    EXPECT_EQ(m1, Money(50.02));
    
    m1 *= Money();
    EXPECT_EQ(m1, Money(0));

    Money m3(99.99);
    Money m4(1);
    m3 *= m4;
    EXPECT_EQ(m3, Money(99.99));
}

// TEST(ArithmeticSet, DivEqOp) {

// }


TEST(ArithmeticSet, SumOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    EXPECT_EQ(m1 + m2, Money(15.12));
    
    EXPECT_EQ(m1 + Money(), Money(10.23));

    Money m3(99.99);
    Money m4(99.91);
    EXPECT_EQ(m3 + m4, Money(199.9));
}

TEST(ArithmeticSet, SubOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    EXPECT_EQ(m1 - m2, Money(5.34));
    
    EXPECT_EQ(m1 - Money(), Money(10.23));

    Money m3(99.99);
    Money m4(99.91);
    EXPECT_EQ(m3 - m4, Money(0.08));
    std::cout << (m4 < m3) << '\n';
    EXPECT_THROW(m4 - m3, std::invalid_argument);
}

TEST(ArithmeticSet, MulOp) {
    Money m1(10.23);
    Money m2(4.89);
    
    EXPECT_EQ(m1 * m2, Money(50.02));
    
    EXPECT_EQ(m1 * Money(), Money(0));

    Money m3(99.99);
    Money m4(1);
    EXPECT_EQ(m3 * m4, Money(99.99));
}

// TEST(ArithmeticSet, DivEqOp) {

// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
