#include "common.h"


int is_valid_symbol(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

void invalid_input() {
    printf("Invalid input\n");
}

void allocation_error() {
    printf("Memory allocation error\n");
}
