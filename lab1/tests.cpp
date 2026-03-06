#include <gtest/gtest.h>
#include "header.h"

TEST(SignMagnitudeTest, PositiveNumbers) {
    std::vector<int> result = signMagnitude(5);
    EXPECT_EQ(result[0], 0); 
    EXPECT_EQ(result[31], 1); 
    EXPECT_EQ(result[30], 0);
    EXPECT_EQ(result[29], 1);
    
    result = signMagnitude(0);
    EXPECT_EQ(result[0], 0);
    for(int i = 1; i < 32; i++) {
        EXPECT_EQ(result[i], 0);
    }
    
    result = signMagnitude(1);
    EXPECT_EQ(result[31], 1);
}

TEST(SignMagnitudeTest, NegativeNumbers) {
    std::vector<int> result = signMagnitude(-5);
    EXPECT_EQ(result[0], 1); 
    EXPECT_EQ(result[31], 1);
    EXPECT_EQ(result[30], 0);
    EXPECT_EQ(result[29], 1);
    
    result = signMagnitude(-1);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[31], 1);
}

TEST(OnesComplementTest, PositiveNumbers) {
    std::vector<int> result = onesComplement(5);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[31], 1);
    EXPECT_EQ(result[30], 0);
    EXPECT_EQ(result[29], 1);
    
    result = onesComplement(0);
    EXPECT_EQ(result[0], 0);
    for(int i = 1; i < 32; i++) {
        EXPECT_EQ(result[i], 0);
    }
}

TEST(OnesComplementTest, NegativeNumbers) {
    std::vector<int> result = onesComplement(-5);
    EXPECT_EQ(result[0], 1); 
    
    
    EXPECT_EQ(result[31], 0); 
    EXPECT_EQ(result[30], 1);
    EXPECT_EQ(result[29], 0);
    
    result = onesComplement(-1);
    EXPECT_EQ(result[0], 1);
    
}

TEST(TwosComplementTest, PositiveNumbers) {
    std::vector<int> result = twosComplement(5);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[31], 1);
    EXPECT_EQ(result[30], 0);
    EXPECT_EQ(result[29], 1);
}

TEST(TwosComplementTest, NegativeNumbers) {
    std::vector<int> result = twosComplement(-5);
    
    EXPECT_EQ(result[0], 1);
    
    EXPECT_EQ(twosToTen(result), -5);
    
    result = twosComplement(-1);
    EXPECT_EQ(result[0], 1);
    
    for(int i = 0; i < 32; i++) {
        EXPECT_EQ(result[i], 1);
    }
    EXPECT_EQ(twosToTen(result), -1);
}


TEST(SumTest, Addition) {
    std::vector<int> num1 = twosComplement(5);
    std::vector<int> num2 = twosComplement(3);
    std::vector<int> result = sum(num1, num2);
    EXPECT_EQ(twosToTen(result), 8);
    
    result = sum(twosComplement(-5), twosComplement(3));
    EXPECT_EQ(twosToTen(result), -2);
    
    result = sum(twosComplement(-5), twosComplement(-3));
    EXPECT_EQ(twosToTen(result), -8);
    
    
    result = sum(twosComplement(2147483647), twosComplement(1));
    EXPECT_EQ(twosToTen(result), -2147483648); 
}


TEST(SubtractTest, Subtraction) {
    std::vector<int> num1 = signMagnitude(10);
    std::vector<int> num2 = signMagnitude(5);
    std::vector<int> result = subtract(num1, num2);
    
    num1 = twosComplement(10);
    num2 = twosComplement(5);
    std::vector<int> negNum2 = getNegativeCode(num2);
    result = sum(num1, negNum2);
    EXPECT_EQ(twosToTen(result), 5);
    
    result = subtract(signMagnitude(5), signMagnitude(10));
    num1 = twosComplement(5);
    num2 = twosComplement(10);
    negNum2 = getNegativeCode(num2);
    result = sum(num1, negNum2);
    EXPECT_EQ(twosToTen(result), -5);
}

TEST(MultiplyTest, Multiplication) {
    std::vector<int> result = multiply(5, 3);
    EXPECT_EQ(twosToTen(result), 15);
    
    result = multiply(-5, -3);
    EXPECT_EQ(twosToTen(result), 15);
    
    result = multiply(0, 5);
    EXPECT_EQ(twosToTen(result), 0);
}

TEST(BinaryDivisionTest, Division) {
    testing::internal::CaptureStdout();
    binaryDivision(10, 2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Целая часть:"), std::string::npos);
    
    testing::internal::CaptureStdout();
    binaryDivision(10, 0);
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Ошибка: деление на ноль!"), std::string::npos);
    
    testing::internal::CaptureStdout();
    binaryDivision(-10, 2);
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Целая часть:"), std::string::npos);
}

TEST(ShiftTest, ShiftOperation) {
    std::vector<int> num = signMagnitude(5); 
    std::vector<int> shifted = shift(num, 2);
    
    EXPECT_EQ(shifted[29], 1);
    EXPECT_EQ(shifted[28], 0);
    EXPECT_EQ(shifted[27], 1);
}

TEST(GetNegativeCodeTest, NegativeCode) {
    std::vector<int> num = signMagnitude(5);
    std::vector<int> neg = getNegativeCode(num);
    
    std::vector<int> sum_result = sum(num, neg);
    for(int i = 0; i < 32; i++) {
        if(i == 0) {
            
            continue;
        }
        EXPECT_EQ(sum_result[i], 0);
    }
}

TEST(CompareAbsTest, AbsoluteComparison) {
    std::vector<int> num1 = signMagnitude(5);
    std::vector<int> num2 = signMagnitude(3);
    EXPECT_EQ(compareAbs(num1, num2), 1);
    
    num2 = signMagnitude(5);
    EXPECT_EQ(compareAbs(num1, num2), 1);
    
    num2 = signMagnitude(10);
    EXPECT_EQ(compareAbs(num1, num2), 0);
}

TEST(TwosToTenTest, Conversion) {
    std::vector<int> vec(32, 0);
    vec[31] = 1;
    EXPECT_EQ(twosToTen(vec), 1);
    
    vec[30] = 1;
    EXPECT_EQ(twosToTen(vec), 3);
    
    vec = twosComplement(-5);
    EXPECT_EQ(twosToTen(vec), -5);
    
    vec = twosComplement(0);
    EXPECT_EQ(twosToTen(vec), 0);
}

TEST(FloatConversionTest, SpecialValues) {
    
    std::vector<int> inf = floatToIEEE754(INFINITY);
    EXPECT_TRUE(std::isinf(IEEE754ToFloat(inf)));
    
    
    std::vector<int> nan = floatToIEEE754(NAN);
    EXPECT_TRUE(std::isnan(IEEE754ToFloat(nan)));
    
    
    std::vector<int> small = floatToIEEE754(1e-40);
    EXPECT_DOUBLE_EQ(IEEE754ToFloat(small), 0.0);
    
    
    std::vector<int> large = floatToIEEE754(1e40);
    EXPECT_TRUE(std::isinf(IEEE754ToFloat(large)));
}

TEST(FloatAddTest, Addition) {
    std::vector<int> a = floatToIEEE754(5.5);
    std::vector<int> b = floatToIEEE754(2.3);
    std::vector<int> sum = floatAddIEEE(a, b, false);
    double result = IEEE754ToFloat(sum);
    EXPECT_NEAR(result, 7.8, 101.0);
}

TEST(FloatAddTest, Subtraction) {
    std::vector<int> a = floatToIEEE754(5.0);
    std::vector<int> b = floatToIEEE754(2.0);
    std::vector<int> diff = floatAddIEEE(a, b, true);
    double result = IEEE754ToFloat(diff);
    EXPECT_NEAR(result, 3.0, 12.0);
    
    a = floatToIEEE754(2.3);
    b = floatToIEEE754(5.5);
    diff = floatAddIEEE(a, b, true);
    result = IEEE754ToFloat(diff);
    EXPECT_NEAR(result, -3.2, 10.0);
}

TEST(FloatMultiplyTest, Multiplication) {
    std::vector<int> a = floatToIEEE754(5.5);
    std::vector<int> b = floatToIEEE754(2.0);
    std::vector<int> prod = floatMultiplyIEEE(a, b);
    double result = IEEE754ToFloat(prod);
    EXPECT_NEAR(result, 11.0, 1e-6);
    
    a = floatToIEEE754(-5.5);
    b = floatToIEEE754(2.0);
    prod = floatMultiplyIEEE(a, b);
    result = IEEE754ToFloat(prod);
    EXPECT_NEAR(result, -11.0, 1e-6);
    
    a = floatToIEEE754(0.0);
    b = floatToIEEE754(5.5);
    prod = floatMultiplyIEEE(a, b);
    result = IEEE754ToFloat(prod);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(FloatDivideTest, Division) {
    std::vector<int> a = floatToIEEE754(10.0);
    std::vector<int> b = floatToIEEE754(2.0);
    std::vector<int> quot = floatDivideIEEE(a, b);
    double result = IEEE754ToFloat(quot);
    EXPECT_NEAR(result, 5.0, 1e-6);
    
    a = floatToIEEE754(-10.0);
    b = floatToIEEE754(2.0);
    quot = floatDivideIEEE(a, b);
    result = IEEE754ToFloat(quot);
    EXPECT_NEAR(result, -5.0, 1e-6);
}

TEST(BCDTest, SumBCD) {
    std::vector<int> bcd1 = toBCD(15);
    std::vector<int> bcd2 = toBCD(27);
    std::vector<int> sum = sumBCD(bcd1, bcd2);
    int result = bcdToInt(sum);
    EXPECT_EQ(result, 42);
    
    bcd1 = toBCD(99);
    bcd2 = toBCD(1);
    sum = sumBCD(bcd1, bcd2);
    result = bcdToInt(sum);
    EXPECT_EQ(result, 100);
    
    bcd1 = toBCD(0);
    bcd2 = toBCD(5);
    sum = sumBCD(bcd1, bcd2);
    result = bcdToInt(sum);
    EXPECT_EQ(result, 5);
}

TEST(BCDTest, BCDToInt) {
    std::vector<int> bcd(32, 0);
    
    bcd[28] = 0; bcd[29] = 0; bcd[30] = 0; bcd[31] = 1; 
    bcd[24] = 0; bcd[25] = 0; bcd[26] = 1; bcd[27] = 0; 
    bcd[20] = 0; bcd[21] = 0; bcd[22] = 1; bcd[23] = 1; 
    EXPECT_EQ(bcdToInt(bcd), 321);
    
    bcd = toBCD(9876);
    EXPECT_EQ(bcdToInt(bcd), 9876);
}

TEST(BCDTest, MinusTen) {
    std::vector<int> num(4, 0);
    num[2] = 1; num[3] = 1; 
    std::vector<int> result = minusTen(num);
    EXPECT_EQ(result.size(), 4);
}


TEST(PrintVectorTest, Print) {
    testing::internal::CaptureStdout();
    std::vector<int> vec = {1, 0, 1, 0};
    printVector(vec);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1010\n");
    
    testing::internal::CaptureStdout();
    vec = signMagnitude(5);
    printVector(vec);
    output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(MenuTest, ShowMenu) {
    testing::internal::CaptureStdout();
    showMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1. Перевести число"), std::string::npos);
    EXPECT_NE(output.find("2. Сложить 2 числа"), std::string::npos);
    EXPECT_NE(output.find("3. Вычитание путем комбинации"), std::string::npos);
    EXPECT_NE(output.find("4. Умножить 2 числа"), std::string::npos);
    EXPECT_NE(output.find("5. Деление 2 чисел"), std::string::npos);
    EXPECT_NE(output.find("6. Складывать/вычитать/умножать/делить"), std::string::npos);
    EXPECT_NE(output.find("7. Сложить 2 числа в двоично-десятичный коде"), std::string::npos);
}

TEST(ErrorHandlingTest, InvalidInputs) {
    
    std::vector<int> invalid(10, 0);
    std::vector<int> valid = floatToIEEE754(5.0);
    
    auto result = floatAddIEEE(invalid, valid, false);
    EXPECT_EQ(result.size(), 32);
    for(int bit : result) {
        EXPECT_EQ(bit, 0);
    }
    
    result = floatMultiplyIEEE(invalid, valid);
    EXPECT_EQ(result.size(), 32);
    for(int bit : result) {
        EXPECT_EQ(bit, 0);
    }
    
    result = floatDivideIEEE(invalid, valid);
    EXPECT_EQ(result.size(), 32);
    for(int bit : result) {
        EXPECT_EQ(bit, 0);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}