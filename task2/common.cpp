#include "common.h"
#include <iostream>

bool is_valid_symbol(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

void invalid_input() {
    std::cout << "Invalid input\n";
}
