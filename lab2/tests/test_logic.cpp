#include "../include/table.h"
#include "../include/opz.h"
#include "../include/exceptions.h"
#include <iostream>
#include <string>
#include <map>

void safe_run(std::string expr, int mode = 3) {
    try {
        Table::generate(expr, mode);
    } catch (...) {}
}

int main() {
    safe_run("!(a & b) | (c ~ d) -> e"); 
    safe_run("a->b");
    std::string formula = "a & b | !c";
    for(int i = 3; i <= 12; i++) {
        safe_run(formula, i);
    }
    safe_run("(a&b))");      
    safe_run("((a&b)");      
    safe_run("a & b (");     
    safe_run("a & b &");     
    safe_run("!");           
    safe_run("!a&b");
    safe_run("a|b~c");

    return 0;
}