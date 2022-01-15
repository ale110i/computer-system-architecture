#pragma once

#include "encryption.h"
#include <stdio.h>

enum {
    MAX_VALID_CHAR_CODE = 122,
    ALPHABET_SIZE = 62,
    MAX_CONTAINER_SIZE = 10000
};

int is_valid_symbol(char c);

void invalid_input();

void allocation_error();