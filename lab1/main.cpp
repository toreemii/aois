#include "header.h"

int main()
{
    int n;
    int number;
    int num1, num2;
    double num1Double, num2Double;
    std::vector<int> result;
    std::vector<int> num1BiteCode;
    std::vector<int> num2BiteCode;


    std::vector<int> a{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
    std::vector<int> b{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,0,0};
    while (true)
    {
        showMenu();
        std::cout << "Выберите номер от 1 до 8: ";
        while(!getInt(n)) {
                std::cout << "Неверный ввод" << '\n';
        }
        switch (n)
        {
        case 1:
            std::cout << "Введите число в 10-м формате: ";
            while(!getInt(number)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "В прямом: ";
            printVector(signMagnitude(number));
            std::cout << "В обратном: ";
            printVector(onesComplement(number));
            std::cout << "В дополнительном: ";
            printVector(twosComplement(number));
            break;
        case 2:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getInt(num1)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getInt(num2)) {
                std::cout << "Неверный ввод" << '\n';
            }
            num1BiteCode = twosComplement(num1);
            num2BiteCode = twosComplement(num2);
            result = sum(num1BiteCode, num2BiteCode);
            printVector(result);
            std::cout << twosToTen(result) << std::endl;
            break;
        case 3:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getInt(num1)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getInt(num2)) {
                std::cout << "Неверный ввод" << '\n';
            }
            num1BiteCode = twosComplement(num1);
            num2BiteCode = twosComplement(num2);
            result = sum(num1BiteCode, num2BiteCode);
            printVector(result);
            std::cout << twosToTen(result) << std::endl;
            break;
        case 4:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getInt(num1)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getInt(num2)) {
                std::cout << "Неверный ввод" << '\n';
            }
            printVector(multiply(num1, num2));
            std::cout << twosToTen(result) << std::endl;
            break;

        case 5:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getInt(num1)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getInt(num2)) {
                std::cout << "Неверный ввод" << '\n';
            }
            binaryDivision(num1, num2);
            std::cout << twosToTen(result) << std::endl;
            break;

        case 6:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getDouble(num1Double)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getDouble(num2Double)) {
                std::cout << "Неверный ввод" << '\n';
            }
            num1BiteCode = floatToIEEE754(num1Double);
            num2BiteCode = floatToIEEE754(num2Double);
            printVector(floatAddIEEE(num1BiteCode, num2BiteCode, false));
            std::cout << "Результат суммы: " << IEEE754ToFloat(floatAddIEEE(num1BiteCode, num2BiteCode, false)) << std::endl;

            printVector(floatAddIEEE(num1BiteCode, num2BiteCode, true));
            std::cout << "Результат разности: " << IEEE754ToFloat(floatAddIEEE(num1BiteCode, num2BiteCode, true)) << std::endl;

            printVector(floatMultiplyIEEE(num1BiteCode, num2BiteCode));
            std::cout << "Результат умножения: " << IEEE754ToFloat(floatMultiplyIEEE(num1BiteCode, num2BiteCode)) << std::endl;

            printVector(floatDivideIEEE(num1BiteCode, num2BiteCode));
            std::cout << "Результат деления: " << IEEE754ToFloat(floatDivideIEEE(num1BiteCode, num2BiteCode)) << std::endl;
            break;

        case 7:
            std::cout << "Введите 1-ое число в 10-ом формате: \n";
            while(!getInt(num1)) {
                std::cout << "Неверный ввод" << '\n';
            }
            std::cout << "Введите 2-ое число в 10-ом формате: \n";
            while(!getInt(num2)) {
                std::cout << "Неверный ввод" << '\n';
            }
            printVector(sumBCD(toBCD(num1), toBCD(num2)));
            std::cout << bcdToInt(sumBCD(toBCD(num1), toBCD(num2))) << std::endl;
            break;

        default:
            std::cout << "Неверный ввод" << '\n';
            break;
        }
    }
}