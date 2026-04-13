#include "HashTable.h"
#include <cassert>

void run_tests()
{
    MathHashProvider hp;
    HashTable<std::string, std::string> ht(20, hp);

    ht.insert("Set", "Collection of objects");
    assert(ht.size() == 1);

    ht.insert("Set", "Updated Definition");
    std::string val;
    ht.get("Set", val);
    assert(val == "Updated Definition");

    assert(ht.get("Set", val) == true);
    assert(ht.get("NonExist", val) == false);

    assert(ht.remove("Set") == true);
    assert(ht.size() == 0);

    ht.insert("A", "X");
    assert(ht.getLoadFactor() == 1.0 / 20.0);

    std::cout << "All tests passed for coverage!" << std::endl;
}

int main()
{
    run_tests();
    return 0;
}