#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>   
#include <limits> 

std::vector<int> signMagnitude(int number);
void showMenu();
std::vector<int> onesComplement(int number);
std::vector<int> twosComplement(int number);
std::vector<int> sum(std::vector<int> number1, std::vector<int> number2);
void printVector(std::vector<int> vec);
std::vector<int> multiply(int number1, int number2);
std::vector<int> shift(std::vector<int> num, int n);
std::vector<int> toBCD(int num);
std::vector<int> sumBCD(std::vector<int> num1, std::vector<int> num2);
std::vector<int> minusTen(std::vector<int> num1);


std::vector<int> subtract(std::vector<int> num1, std::vector<int> num2);
int compareAbs(const std::vector<int>& num1, const std::vector<int>& num2);
void binaryDivision(int number1, int number2);
std::vector<int> getNegativeCode(std::vector<int> num);


void printVectorDouble(std::vector<int> vec);
std::vector<int> floatToIEEE754(double value);
double IEEE754ToFloat(const std::vector<int>& bits);
std::vector<int> floatAddIEEE(const std::vector<int>& a, const std::vector<int>& b, bool isSub);
std::vector<int> floatMultiplyIEEE(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> floatDivideIEEE(const std::vector<int>& dividend, const std::vector<int>& divisor);


int twosToTen(std::vector<int> vec);
int bcdToInt(const std::vector<int>& vec);

bool getInt(int& value);
bool getDouble(double& value);