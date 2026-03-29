#include "../include/menu.h"
#include "../include/table.h"
#include "../include/exceptions.h"
#include <iostream>
#include <string>
#include <limits>

void Menu::run()
{
    int choice = -1;
    std::string formula;

    while (true)
    {
        std::cout << "\n========== МЕНЮ ЛАБОРАТОРНОЙ №2 ==========" << std::endl;
        std::cout << "1. Ввод функции" << std::endl;
        std::cout << "2. Построить таблицу истинности" << std::endl;
        std::cout << "3. Построить СДНФ и СКНФ" << std::endl;
        std::cout << "4. Вывести числовую форму (Sum/Mult)" << std::endl;
        std::cout << "5. Вывести индексную форму (Номер)" << std::endl;
        std::cout << "6. Определение классов Поста (T0, T1, S, M, L)" << std::endl;
        std::cout << "7. Построение Полинома Жегалкина" << std::endl;
        std::cout << "8. Поиск фиктивных переменных" << std::endl;
        std::cout << "9. Булево дифференцирование" << std::endl;
        std::cout << "10. Расчетная минимизация (метод Квайна)" << std::endl;
        std::cout << "11.Расчетно-табличная минимизация (Квайн-МакКласки)"<<std::endl;
        std::cout << "12. Карта Карно" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Выберите пункт: ";

        if (!(std::cin >> choice))
        {
            std::cout << "Ошибка! Введите число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0)
            break;
        if (choice < 1 || choice > 12)
        {
            std::cout << "Неверный пункт!" << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите формулу: ";
        std::getline(std::cin, formula);

        try
        {
            Table::generate(formula, choice);
        }
        catch (const LogicalError &e)
        {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}