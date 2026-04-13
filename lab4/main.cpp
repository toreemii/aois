#include <iostream>
#include "HashTable.h"

void displayMenu()
{
    std::cout << "\n--- МЕНЮ ХЕШ-ТАБЛИЦЫ (МАТЕМАТИКА) ---" << std::endl;
    std::cout << "1. Добавить новый термин (Create)" << std::endl;
    std::cout << "2. Найти определение (Read)" << std::endl;
    std::cout << "3. Удалить термин (Delete)" << std::endl;
    std::cout << "4. Показать всю таблицу и статистику" << std::endl;
    std::cout << "5. Выход" << std::endl;
    std::cout << "Выберите пункт: ";
}

void seedData(HashTable<std::string, std::string> &ht)
{
    ht.insert("Algebra", "Study of mathematical symbols");
    ht.insert("Geometry", "Branch concerned with sizes and shapes");
    ht.insert("Logic", "Study of valid reasoning");
    ht.insert("Number", "Arithmetical value");
    ht.insert("Graph", "Structure of nodes and edges");
    ht.insert("Prime", "Natural number greater than 1");
    ht.insert("Subset", "Set within another set");
    ht.insert("Radius", "Distance from center to edge");
    ht.insert("Angle", "Space between two intersecting lines");
    ht.insert("Origin", "Point (0,0) in coordinate system");
    ht.insert("A", "Point A");
    ht.insert("U", "Union set");
    ht.insert("i", "Imaginary unit");
}

int main()
{
    MathHashProvider hp;
    HashTable<std::string, std::string> myTable(20, hp);

    seedData(myTable);

    int choice;
    std::string key, value;

    while (true)
    {
        displayMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 5)
            break;

        switch (choice)
        {
        case 1:
            std::cout << "Термин: ";
            std::cin >> key;
            if (myTable.get(key, value))
            {
                std::cout << "ВНИМАНИЕ: Такой ключ уже есть! Данные будут обновлены." << std::endl;
            }
            std::cout << "Определение: ";
            std::cin.ignore();
            std::getline(std::cin, value);
            myTable.insert(key, value);
            break;
        case 2:
            std::cout << "Искать: ";
            std::cin >> key;
            if (myTable.get(key, value))
                std::cout << "Значение: " << value << std::endl;
            else
                std::cout << "Не найдено!" << std::endl;
            break;
        case 3:
            std::cout << "Удалить: ";
            std::cin >> key;
            if (myTable.remove(key))
                std::cout << "Удалено." << std::endl;
            else
                std::cout << "Ключ не найден." << std::endl;
            break;
        case 4:
            myTable.printExtended();
            std::cout << "\nСтатистика:" << std::endl;
            std::cout << "- Заполнено строк: " << myTable.size() << std::endl;
            std::cout << "- Коэффициент заполнения: " << myTable.getLoadFactor() << std::endl;
            break;
        }
    }
    return 0;
}